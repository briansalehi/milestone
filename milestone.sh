#!/usr/bin/env bash

read -n 1 -p "Do you want to [P]ractice or [S]tudy? " mode
echo
echo

last_line=$(($(tput lines) - 2))
declare -A subjects
declare -A topics
declare -A resources
declare -A sections
margin=4

dense_column()
{
    local line=0
    local max_line_width=0
    local max_width=$(tput cols)
    local screen_lines=$(tput lines)
    local total_lines=0
    local max_columns=0
    local column_number=0
    local line_number=0
    local remaining_line=0
    local min_axes=0
    local line_length=0
    local line_bytes=0
    local last_column=0
    local buffer=""

    buffer="$(mktemp)"

    while read -r line
    do
        echo "$line" >> "$buffer"
        total_lines=$((total_lines + 1))
        line_length="$(sed -E 's/\x1B\[[0-9;]*[mK]//g' <<< "$line" | wc -c)"
        [[ "${line_length}" -gt "$max_line_width" ]] && max_line_width="${line_length}" && line_bytes=${#line}
    done

    max_line_width=$((max_line_width + $margin))
    line_bytes=$((line_bytes + $margin))
    max_columns=$((max_width / max_line_width))
    [[ $((max_width % max_line_width)) -le $margin ]] && max_columns=$((max_columns + 1))
    [[ $((total_lines % max_columns)) -gt 0 ]] && remaining_line=1
    max_lines=$((total_lines / max_columns + remaining_line))

    if [[ $max_lines -gt $screen_lines ]]
    then
        for line_number in $(seq 1 $max_lines)
        do
            for column_number in $(seq $line_number $max_lines $total_lines)
            do
                last_column=$(seq $line_number $max_lines $total_lines | tail -n1)
                line="$(sed -n "$((column_number))p" "$buffer")"

                if [[ $column_number -eq $last_column ]]
                then
                    printf "%-$((line_bytes - margin))s" "$line"
                else
                    printf "%-${line_bytes}s" "$line"
                fi
            done
            echo
        done | less -RFX
    else
        for line_number in $(seq 1 $max_lines)
        do
            for column_number in $(seq $line_number $max_lines $total_lines)
            do
                last_column=$(seq $line_number $max_lines $total_lines | tail -n1)
                line="$(sed -n "$((column_number))p" "$buffer")"

                if [[ $column_number -eq $last_column ]]
                then
                    printf "%-$((line_bytes - margin))s" "$line"
                else
                    printf "%-${line_bytes}s" "$line"
                fi
            done
            echo
        done
    fi

    rm "$buffer"
}

start_practice()
{
    while IFS='|' read -r id name
    do
        subjects[$id]="$name"
    done < <(psql -U milestone -d milestone -c "select id, name from subjects order by id" -At)

    while IFS='|' read -r id name
    do
        echo -e "\e[1;35m$id\e[0m \e[1;36m$name\e[0m"
    done < <(psql -U milestone -d milestone -c "select id, name from subjects order by id" -At) | dense_column

    while true
    do
        read -p "Select a subject: " subject
        [[ -n "${subjects[$subject]}" ]] && break
    done

    while IFS="|" read -r id name
    do
        topics[$id]="$name"
    done < <(psql -U milestone -d milestone -c "select id, name from topics where subject_id = $subject order by position, creation" -At)

    while IFS="|" read -r id name
    do
        echo -e "\e[1;35m$id\e[0m \e[1;36m$name\e[0m"
    done < <(psql -U milestone -d milestone -c "select id, name from topics where subject_id = $subject order by position, creation" -At) | dense_column

    while true
    do
        read -p "Select a topic: " topic
        echo "Topic ${topics[$topic]} selected"
        [[ -n "${topics[$topic]}" ]] && break
    done

    practice_count="$(psql -U milestone -d milestone -c "select count(id) from practices where topic_id = $topic" -At)"
    practice_number=0

    while IFS="|" read -r practice heading
    do
        practice_number=$((practice_number + 1))
        practices[$practice]="$parent"

        clear
        printf "\e[1;35m%d/%d\e[0m \e[2;37m%*s\e[0m\n\e[1;33m%-s\e[0m\n" $practice_number $practice_count $(($(tput cols) - ${#practice_number} - ${#practice_count} - 2)) $practice "$heading"

        while IFS="|" read -r block type language
        do
            content="$(psql -U milestone -d milestone -c "select content from practice_blocks where id = $block" -At)"

            printf "\e[2;37m%*s\e[0m" $(tput cols) $type $language $block
            case "$type" in
                text) echo "$content" | bat --paging never --squeeze-blank --language "md" --style "plain" ;;
                code) echo "$content" | bat --paging never --squeeze-blank --language "$language" --style "grid,numbers" ;;
                *) echo -e "\e[1;31mInvalid block type and language $type / $language" ;;
            esac
            echo
        done < <(psql -U milestone -d milestone -c "select id, type, language from practice_blocks where practice_id = $practice order by position" -At)

        while true
        do
            tput cup $last_line 0
            read -n 1 -p "Press [N]ext to move forward: " response </dev/tty
            [[ "${response,,}" == "n" ]] && break
        done
    done < <(psql -U milestone -d milestone -c "select id, heading from practices where topic_id = $topic" -At)
    echo
}

start_study()
{
    while IFS='|' read -r id name
    do
        resources[$id]="$name"
    done < <(psql -U milestone -d milestone -c "select id, name from resources order by name" -At)

    while IFS='|' read -r id name
    do
        echo -e "\e[1;35m$id\e[0m \e[1;36m$name\e[0m"
    done < <(psql -U milestone -d milestone -c "select id, name from resources order by name" -At) | dense_column
    echo

    while true
    do
        read -p "Select a resource: " resource
        [[ -n "${resources[$resource]}" ]] && break
    done

    while IFS="|" read -r id name
    do
        sections[$id]="$name"
    done < <(psql -U milestone -d milestone -c "select id, number from sections where resource_id = $resource order by number, created" -At)

    while IFS="|" read -r id name
    do
        echo -e "\e[1;35m$id\e[0m \e[1;36m$name\e[0m"
    done < <(psql -U milestone -d milestone -c "select id, number from sections where resource_id = $resource order by number, created" -At) | dense_column
    echo

    while true
    do
        read -p "Select a section: " section
        echo "Topic ${sections[$section]} selected"
        [[ -n "${sections[$section]}" ]] && break
    done
    echo

    note_count="$(psql -U milestone -d milestone -c "select count(id) from notes where section_id = $section" -At)"
    note_number=0

    while IFS="|" read -r note heading
    do
        note_number=$((note_number + 1))
        notes[$note]="$parent"

        clear
        printf "\e[1;35m%d/%d\e[0m \e[2;37m%*s\e[0m\n\e[1;33m%-s\e[0m\n" $note_number $note_count $(($(tput cols) - ${#note_number} - ${#note_count} - 2)) $note "$heading"

        while IFS="|" read -r block type language
        do
            content="$(psql -U milestone -d milestone -c "select content from note_blocks where id = $block" -At)"

            printf "\e[2;37m%*s\e[0m" $(tput cols) "$type $language $block"
            case "$type" in
                text) echo "$content" | bat --paging never --squeeze-blank --language "md" --style "plain" ;;
                code) echo "$content" | bat --paging never --squeeze-blank --language "$language" --style "grid,numbers" ;;
                *) echo -e "\e[1;31mInvalid block type and language $type / $language" ;;
            esac
            echo
        done < <(psql -U milestone -d milestone -c "select id, type, language from note_blocks where note_id = $note order by position" -At)

        while true
        do
            tput cup $last_line 0
            read -n 1 -p "Press [N]ext to move forward: " response </dev/tty
            [[ "${response,,}" == "n" ]] && break
        done
    done < <(psql -U milestone -d milestone -c "select id, heading from notes where section_id = $section" -At)
    echo
}

case "${mode,,}" in
    s|study) start_study ;;
    p|practice) start_practice ;;
    *) echo -e "\e[1;31mIncorrect mode selected\e[0m" ;;
esac
