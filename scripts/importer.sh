#!/usr/bin/env bash

error() { tput setaf 1; tput bold; echo "$@" >&2; tput sgr0; exit 1; }
report_progress()
{
    local counter="${1:-0}"
    local length

    if [ "$counter" -eq 0 ]
    then
        echo -n "${2:-Untitled}: $counter"
    else
        length="$(echo -n "$((counter - 1))" | wc -c)"
        printf "%.s\b" $(seq 1 "$length")
        echo -n "$counter"
    fi
}

declare -A subjects
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

subject_index=0
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
subject_id=0

topic_index=0
for subject in "${!subjects[@]}"
do
    while read -r topic
    do
        report_progress $topic_index "Collecting Topics"
        subject_id=$(psql -U flashback_importer -d flashback -At -c "select id from flashback.subjects where name = '${subjects[$subject]}';")
        topic_entries+=( "${topic_entries[*]:+, }('${topic}', '${subject_id}')" )
        topic_index=$((topic_index + 1))
    done <<< "$(grep -E '^##\s+' "/tmp/references/subjects/${subject}/${subject}.md" | sed 's/^##\s*//')"

    subject_id=0
    subject_index=$((subject_index + 1))
done
echo

topics_query="insert into flashback.topics (name, subject_id) values ${topic_entries[*]};"

# recreate database
psql -U postgres -d flashback -c "\i $PWD/design/database.sql"

# import subjects
psql -U flashback_importer -d flashback -c "${subjects_query}"

# import topics
psql -U flashback_importer -d flashback -c "${topics_query}"

