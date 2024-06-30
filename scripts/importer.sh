#!/usr/bin/env bash

error() { tput setaf 1; tput bold; echo "$@" >&2; tput sgr0; exit 1; }
report_progress()
{
    local counter="${1:-0}"
    local length

    if [ "$counter" -eq 1 ]
    then
        echo -n "${2:-Untitled}: $counter"
    else
        length="$(echo -n "$((counter - 1))" | wc -c)"
        printf "%.s\b" $(seq 1 "$length")
        echo -n "$counter"
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
psql -U postgres -d flashback -c "\i $PWD/design/database.sql"

subject_index=1
for subject in /tmp/references/subjects/*
do
    report_progress $subject_index "Collecting Subjects"
    subject_path="$(basename "$subject")"
    subject_name="$(sed -n '1{s/#\s*//p}' "/tmp/references/subjects/${subject_path}/${subject_path}.md")"
    subject_entries+=( "${subject_entries:+, }('${subject_name}')" )
    subjects["${subject_path}"]="${subject_name}"
    subject_index=$((subject_index + 1))
done
echo

subjects_query="insert into flashback.subjects (name) values ${subject_entries[*]};"

# import subjects
psql -U flashback_importer -d flashback -c "${subjects_query}"

subject_id=1
topic_index=1
for subject in "${!subjects[@]}"
do
    while read -r topic
    do
        report_progress $topic_index "Collecting Topics"
        subject_id=$(psql -U flashback_importer -d flashback -At -c "select id from flashback.subjects where name = '${subjects[$subject]}';")
        subject_records[$subject_id]="${subjects[$subject]}"
        topic_entries+=( "${topic_entries[*]:+, }('${topic}', '${subject_id}')" )
        topic_index=$((topic_index + 1))
    done <<< "$(grep -E '^##\s+' "/tmp/references/subjects/${subject}/${subject}.md" | sed 's/^##\s*//')"

    subject_id=0
    subject_index=$((subject_index + 1))
done
echo

topics_query="insert into flashback.topics (name, subject_id) values ${topic_entries[*]};"

# import topics
psql -U flashback_importer -d flashback -c "${topics_query}"

declare -A topic_records
while read -r record
do
    [ -z "${record#*=}" ] && continue
    [ -z "${record%=*}" ] && continue
    topic_records["${record#*=}"]="${record%=*}"
done <<< "$(psql -U flashback_importer -d flashback -At -c 'select id, name from flashback.topics;' | sed 's/\(.*\)|\(.*\)/\1=\2/')"

declare -A topic_subject_mapping
while read -r record
do
    [ -z "${record#*=}" ] && continue
    [ -z "${record%=*}" ] && continue
    topic_subject_mapping["${record%=*}"]="${record#*=}"
done <<< "$(psql -U flashback_importer -d flashback -At -c 'select t.id, s.id from flashback.subjects s join flashback.topics t on t.subject_id = s.id;' | sed 's/\(.*\)|\(.*\)/ [\1]="\2"/' | tr -d '\n')"

practice_index=1
rough_total="$(grep -rw '<details>' /tmp/references/subjects | wc -l)"
echo "Rough total: $rough_total"
declare -a practice_entries
for subject in "${!subjects[@]}"
do
    subject="/tmp/references/subjects/${subject}/${subject}.md"
    inside_block=0
    current_topic=
    blocks=
    heading=

    while read -r line
    do
        if grep -q '## ' <<< "$line"
        then
            current_topic="${line/\#\# /}"
        elif [ "${line/> /}" == "---" ]
        then
            continue
        elif grep -q '<details>' <<< "$line"
        then
            inside_block=1
        elif grep -q '<summary>' <<< "$line"
        then
            heading="$(sed 's/<.\?summary>//g' <<< "$line")"
        elif grep -q '</details>' <<< "$line"
        then
            inside_block=0
            topic_id="${topic_records[$current_topic]}"
            blocks="${blocks//\'/}"
            heading="${heading//\'/}"

            practice_id="$(psql -U flashback_importer -d flashback -Aqt -c "insert into flashback.practices (heading, topic_id) values ('${heading}', '$topic_id') returning id;" || error "Practice failed to be inserted")"
            if ! psql -U flashback_importer -d flashback -Aqt -c "insert into flashback.practice_blocks (block, extension, practice_id) values ('${blocks}', 'txt', ${practice_id});"
            then

                echo
                echo ">>>>>>>>>>>>>>>>>>>>>"
                echo "Topic: $topic_id $current_topic"
                echo "$heading"
                echo "${blocks}"
                echo "<<<<<<<<<<<<<<<<<<<<<"
                echo

                error "Practice block failed to be inserted"
            fi

            report_progress $practice_index "Storing practice"
            practice_index=$((practice_index + 1))

            blocks=
        elif [ "$inside_block" -eq 1 ]
        then
            line="${line/> /}"
            line="${line/>/}"
            blocks="$(printf '%s\n%s' "$blocks" "$line")"
        fi
    done < "$subject"
done
echo

