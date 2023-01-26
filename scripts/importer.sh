#!/usr/bin/env bash

base_path="$1"

base_command="psql -U postgres -h localhost -d flashback"
query_command="$base_command -A --csv -c"
insert_command="$base_command -c"

if ! [ -d "$base_path" ]
then
    echo -e "\e[1;31m""base path does not exist${base_path:+: }$base_path""\e[0m"
    exit 1
fi

for entry in "$base_path"/books/*
do
    title="$(sed -n '1s/^# \[\(.*\)\](\(.*\))$/\1/p' "$entry")"
    title="${title//\'/\'\'}"
    link="$(sed -n '1s/^# \[\(.*\)\](\(.*\))$/\2/p'  "$entry")"
    link="${link//\'/\'\'}"

    brief_title="$title"
    brief_link="$(sed -n 's/https:\/\/[w.]\+\?\([^/]\+\).*/\1/p' <<< "$link")"

    [ "${#title}" -gt 25 ] && brief_title="${title:0:30}..."

    if grep -q 'https://' <<< "$link"
    then
        color="\e[1;32m"
    else
        color="\e[1;31m"
    fi

    printf "Resource \e[1;34m %-33s \e[0m($color%s\e[0m)" "$brief_title" "${brief_link:-$link}"

    query_sql="select id from resources where title = '$title';"
    insert_sql="insert into resources (title, purchase_link) values ('$title', '$link');"

    resource_id="$($query_command "$query_sql" 2>/tmp/importer.log | sed '1d')"

    if [ -z "$resource_id" ]
    then
        $insert_command "$insert_sql" >/tmp/importer.log
        echo -e "\e[1;33m"" Imported\e[0m"
    else
        echo -e "\e[1;35m"" Already exists\e[0m"
    fi
done
