#!/usr/bin/env bash

error() { tput setaf 1; tput bold; echo "$@" >&2; tput sgr0; exit 1; }
alert()
{
    tput bold
    if [ $# -eq 1 ]
    then
        tput setaf 5
        echo -e "$1"
    else
        tput setaf 4
        echo -ne "$1: "
        tput setaf 8
        echo -e "$2"
    fi
    tput sgr0
}
notice()
{
    [ "${DEBUG:-0}" -ne 1 ] && return
    alert "$1" "$2"
}
log()
{
    [ "${DEBUG:-0}" -ne 1 ] && return

    tput bold
    if [ $# -eq 1 ]
    then
        tput setaf 5
        echo -e "$1"
    else
        tput setaf 4
        echo -ne "$1: "
        tput setaf 8
        read -rp "$2" </dev/tty
    fi
    tput sgr0
}
report_progress()
{
    local counter="${1:-0}"
    local total="$3"
    local length

    if [ "$counter" -eq "${total:-0}" ]
    then
        length="$(echo -n "$((counter - 1))${total:+/}${total}" | wc -c)"
        printf "%.s\b" $(seq 1 "$length")
        [ "$total" -gt 1 ] && echo "$counter${total:+/}${total}"
        [ "$total" -eq 1 ] && echo "${2:-Untitled}: $counter${total:+/}${total}"
    elif [ "$counter" -eq 1 ]
    then
        echo -n "${2:-Untitled}: $counter${total:+/}${total}"
    else
        length="$(echo -n "$((counter - 1))${total:+/}${total}" | wc -c)"
        printf "%.s\b" $(seq 1 "$length")
        echo -n "$counter${total:+/}${total}"
    fi
}

declare -A subjects
declare -A subject_records
declare -a subject_entries
declare -a topic_entries

if [ ! -s "$PWD/design/database.sql" ]
then
    error "Database initial script cannot be found in $PWD/design/database.sql"
fi

if [ ! -d /tmp/references ]
then
    git clone https://github.com/briansalehi/references.git /tmp/references
fi

# recreate database
psql -q -U postgres -c "\i $PWD/design/database.sql" || error "Cannot recreate database"

subject_index=1
total_subjects=$(find /tmp/references/subjects -mindepth 1 -maxdepth 1 | wc -l)
for subject in /tmp/references/subjects/*
do
    report_progress $subject_index "Collecting Subjects" "$total_subjects"
    subject_path="$(basename "$subject")"
    subject_name="$(sed -n '1{s/#\s*//p}' "/tmp/references/subjects/${subject_path}/${subject_path}.md")"
    subject_entries+=( "${subject_entries:+, }('${subject_name}')" )
    subjects["${subject_path}"]="${subject_name}"
    subject_index=$((subject_index + 1))
done

subjects_query="insert into flashback.subjects (name) values ${subject_entries[*]};"

# import subjects
report_progress 1 "Storing Subjects" 1
psql -q -U postgres -d flashback -c "${subjects_query}" || error "Cannot store subjects"

subject_id=1
topic_index=1
total_topics="$(find /tmp/references/subjects/ -mindepth 2 -maxdepth 2 -type f -name '*.md' -not -name 'README.md' -exec grep '^## ' {} \; | wc -l)"
for subject in "${!subjects[@]}"
do
    while read -r topic
    do
        [ -z "$topic" ] && continue
        report_progress $topic_index "Collecting Topics" "$total_topics"
        subject_id=$(psql -U postgres -d flashback -At -c "select id from flashback.subjects where name = '${subjects[$subject]}';")
        subject_records[$subject_id]="${subjects[$subject]}"
        topic_entries+=( "${topic_entries[*]:+, }('${topic}', '${subject_id}')" )
        topic_index=$((topic_index + 1))
    done <<< "$(find /tmp/references/subjects/${subject} -mindepth 1 -maxdepth 1 -type f -name "${subject}.md" -exec grep -E '^##\s+\w+' {} \; | sed 's/^##\s//')"

    subject_id=0
    subject_index=$((subject_index + 1))
done

topics_query="insert into flashback.topics (name, subject_id) values ${topic_entries[*]};"

# import topics
psql -q -U postgres -d flashback -c "${topics_query}" || error "Cannot store topics"

declare -A topic_records
while read -r record
do
    [ -z "${record#*=}" ] && continue
    [ -z "${record%=*}" ] && continue
    topic_records["${record#*=}"]="${record%=*}"
done <<< "$(psql -U postgres -d flashback -At -c 'select id, name from flashback.topics;' | sed 's/\(.*\)|\(.*\)/\1=\2/' || error "Cannot collect topics")"

declare -A topic_subject_mapping
while read -r record
do
    [ -z "${record#*=}" ] && continue
    [ -z "${record%=*}" ] && continue
    topic_subject_mapping["${record%=*}"]="${record#*=}"
done <<< "$(psql -U postgres -d flashback -At -c 'select t.id, s.id from flashback.subjects s join flashback.topics t on t.subject_id = s.id;' | sed 's/\(.*\)|\(.*\)/ [\1]="\2"/' | tr -d '\n' || error "Cannot collect subject and topic identifiers")"

practice_index=1
declare -a blocks=()
declare -a resources=()
declare -a references=()
total_practices="$(find /tmp/references/subjects/ -mindepth 2 -maxdepth 2 -type f -name '*.md' -not -name 'README.md' -exec grep '<details>' {} \; | wc -l)"
for subject in "${!subjects[@]}"
do
    log "Subject" "${subjects[$subject]}"
    subject="/tmp/references/subjects/${subject}/${subject}.md"
    inside_block=0
    code_block=0
    current_topic=
    blocks=()
    resources=()
    references=()
    heading=

    while read -r line
    do
        log "Line" "$line"
        if grep -q '## ' <<< "$line"
        then
            log "Topic Header"
            current_topic="${line/\#\# /}"
        elif [ "${line/> /}" == "---" ]
        then
            log "Horizontal Line"
            resources_block=0
            references_block=0
            code_block=0
            continue
        elif grep -q '<details>' <<< "$line"
        then
            log "Block Begin"
            inside_block=1
        elif grep -q '<summary>' <<< "$line"
        then
            log "Heading"
            heading="$(sed 's/<.\?summary>//g' <<< "$line")"
            read -r line
        elif grep -q '</details>' <<< "$line"
        then
            log "End of Block"
            inside_block=0
            resources_block=0
            references_block=0
            code_block=0
            topic_id="${topic_records[$current_topic]}"
            heading="${heading//\'/\'\'}"

            report_progress $practice_index "Storing practice" "$total_practices"
            practice_index=$((practice_index + 1))

            query="insert into flashback.practices (heading, topic_id) values ('${heading}', '$topic_id') returning id;"
            practice_id="$(psql -U postgres -d flashback -Aqt -c "$query" || error "Practice failed to be inserted" || error "Failed to collect practice identifier")"

            for record in "${blocks[@]}"
            do
                block_type="${record%%:*}"
                record="${record#*:}"
                language="${record%%:*}"
                block="${record#*:}"
                block="${block//\'/\'\'}"

                query="insert into flashback.practice_blocks (content, type, language, practice_id) values ('${block}', '${block_type}', '${language}', ${practice_id});"
                if ! psql -q -U postgres -d flashback -c "$query"
                then
                    alert "\nPractice $practice_id"
                    alert "Query" "$query"
                    alert "Topic" "$topic_id $current_topic"
                    alert "Heading" "$heading"
                    alert "Block" "${blocks[*]}"

                    error "Practice block failed to be inserted"
                fi
            done

            for record in "${resources[@]}"
            do
                record="${record//\'/\'\'}"
                query="insert into flashback.resources (origin, practice_id) values ('${record}', ${practice_id});"
                if ! psql -q -U postgres -d flashback -c "$query"
                then
                    alert "\nPractice $practice_id"
                    alert "Query" "$query"
                    alert "Topic" "$topic_id $current_topic"
                    alert "Heading" "$heading"
                    alert "Block" "${blocks[*]}"
                    alert "Resources" "${resources[*]}"

                    error "Practice block failed to be inserted"
                fi
            done

            for record in "${references[@]}"
            do
                record="${record//\'/\'\'}"
                query="insert into flashback.references (origin, practice_id) values ('${record}', ${practice_id});"
                if ! psql -q -U postgres -d flashback -c "$query"
                then
                    alert "\nPractice $practice_id"
                    alert "Query" "$query"
                    alert "Topic" "$topic_id $current_topic"
                    alert "Heading" "$heading"
                    alert "Block" "${blocks[*]}"
                    alert "Resources" "${resources[*]}"
                    alert "References" "${references[*]}"

                    error "Practice block failed to be inserted"
                fi
            done

            notice "\nPractice $practice_id"
            notice "Topic" "$topic_id $current_topic"
            notice "Heading" "$heading"
            notice "Block" "${blocks[*]}"
            notice "Resources" "${resources[*]}"
            notice "References" "${references[*]}"

            blocks=()
            resources=()
            references=()
        elif [ "$inside_block" -eq 1 ] && grep -Eq '\*+Description\*+' <<< "$line"
        then
            log "Description Ignored"
            continue
        elif [ "$inside_block" -eq 1 ] && grep -Eq '\*+Resources\*+' <<< "$line"
        then
            log "Resources Begin"
            code_block=0
            resources_block=1
            resources=()
        elif [ "$inside_block" -eq 1 ] && grep -Eq '\*+References\*+' <<< "$line"
        then
            log "References Begin"
            code_block=0
            references_block=1
            references=()
        elif [ "$inside_block" -eq 1 ] && [ "${resources_block:-0}" -eq 1 ]
        then
            log "Resource Record"
            resources+=( "${line/> - /}" )
        elif [ "$inside_block" -eq 1 ] && [ "${references_block:-0}" -eq 1 ]
        then
            log "Reference Record"
            references+=( "${line/> - /}" )
        elif [ "$inside_block" -eq 1 ] && grep -Eq '`+\w+$' <<< "$line"
        then
            log "Code Block Begin"
            code_block=1
            language="$(sed 's/.*`\+//' <<< "$line")"
        elif [ "$inside_block" -eq 1 ] && [ "$code_block" -eq 1 ] && grep -Eq '[`]{3,7}$' <<< "$line"
        then
            log "Code Block End"
            blocks+=( "code:$language:$buffer" )
            buffer=
            language=
            code_block=0
        elif [ "$inside_block" -eq 1 ] && [ -z "${line/>/}" ]
        then
            log "Text Block End"
            if [ -n "$buffer" ]
            then
                blocks+=( "text::$buffer" )
            fi
            buffer=
        elif [ "$inside_block" -eq 1 ]
        then
            log "Buffer Line"
            line="${line/> /}"
            line="${line/>/}"
            buffer="$(echo -e "${buffer}${buffer:+\n}${line:-\n}")"
        fi
    done < "$subject"
done

