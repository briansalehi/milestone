#!/usr/bin/env bash

trap 'printf "\r\e[1;31m%-*s\e[0m" $(tput cols) "User Interrupted"; tput cnorm; exit 1' SIGINT

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

    while IFS='|' read -r id name topic_count
    do
        echo -e "\e[1;35m$id\e[0m \e[1;36m$name\e[0m \e[2;37m($topic_count)\e[0m"
    done < <(psql -U milestone -d milestone -c "select s.id, s.name, count(t.id) from subjects s left join topics t on t.subject_id = s.id group by s.id, s.name order by id" -At) | dense_column

    while true
    do
        echo
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
        read -p "Select a topic or type all: " topic
        ( [ -n "${topics[$topic]}" ] || [ "$topic" == "all" ] ) && break
        echo
    done

    local -a selected_topics=()

    if [ "$topic" == "all" ]
    then
        selected_topics=( "${!topics[@]}" )
    else
        selected_topics=( $topic )
    fi

    [ ${#selected_topics[*]} -eq 0 ] && return

    practice_count="$(psql -U milestone -d milestone -c "select count(id) from practices where topic_id in ( $(tr ' ' ',' <<< "${selected_topics[*]}") )" -At)"
    practice_number=0

    while IFS="|" read -r topic topic_name
    do
        while IFS="|" read -r practice heading
        do
            practice_number=$((practice_number + 1))
            practices[$practice]="$parent"
            heading="$(pandoc -f markdown -t plain <<< "$heading" | xargs)"

            clear
            printf "\e[1;36m%s\e[0m \e[2;37m%d\e[0m \e[1;33m>>\e[0m \e[1;36m%s\e[0m \e[2;37m%d\e[0m\n\n" "${subjects[$subject]}" ${subject} "$topic_name" ${topic}
            printf "\e[1;35m%d/%d\e[0m \e[1;33m%s\e[0m \e[2;37m%s\e[0m\n" $practice_number $practice_count "$heading" $practice

            while IFS="|" read -r block type language
            do
                content="$(psql -U milestone -d milestone -c "select content from practice_blocks where id = $block" -At)"

                printf "\e[2;37m%*s\e[0m" $(tput cols) "$type $language $block"
                case "$type" in
                    text) echo "$content" | bat --paging never --squeeze-blank --language "md" --style "plain" ;;
                    code) echo "$content" | bat --paging never --squeeze-blank --language "$language" --style "grid,numbers" ;;
                    *) echo -e "\e[1;31mInvalid block type and language $type / $language" ;;
                esac
                echo
            done < <(psql -U milestone -d milestone -c "select id, type, language from practice_blocks where practice_id = $practice order by position" -At)

            while true
            do
                tput cup $last_line $(($(tput cols) - 28))
                tput civis
                echo -ne "\e[1;31mPress [N]ext to move forward\e[0m"
                read -n 1 -s response </dev/tty
                tput cnorm
                [[ "${response,,}" == "n" ]] && break
            done
        done < <(psql -U milestone -d milestone -c "select id, heading from practices where topic_id = $topic" -At)
    done < <(psql -U milestone -d milestone -c "select id, name from topics where id in ( $(tr ' ' ',' <<< "${selected_topics[*]}") ) order by position, creation" -At)
    echo
}

start_study()
{
    while IFS='|' read -r id name
    do
        resources[$id]="$name"
    done < <(psql -U milestone -d milestone -c "select id, name from resources order by name" -At)

    while IFS='|' read -r id name section_count
    do
        echo -e "\e[1;35m$id\e[0m \e[1;36m$name\e[0m \e[2;37m($section_count)\e[0m"
    done < <(psql -U milestone -d milestone -c "select r.id, r.name, count(s.id) from resources r left join sections s on s.resource_id = r.id group by r.id, r.name order by name" -At) | dense_column

    while true
    do
        read -p "Select a resource: " resource
        [[ -n "${resources[$resource]}" ]] && break
    done

    while IFS="|" read -r id name
    do
        sections[$id]="$name"
    done < <(psql -U milestone -d milestone -c "select id, number from sections where resource_id = $resource order by number, created" -At)

    while IFS="|" read -r id name state
    do
        echo -e "\e[1;35m$id\e[0m \e[1;36m$name\e[0m \e[2;37m($state)\e[0m"
    done < <(psql -U milestone -d milestone -c "select id, number, state from sections where resource_id = $resource order by number, created" -At) | dense_column

    local selected_sections=()

    while true
    do
        read -p "Select a section or type all: " section
        ( [ -n "${sections[$section]}" ] || [ "$section" == "all" ] ) && break
    done
    echo

    if [ "$section" == "all" ]
    then
        selected_sections=( "${!sections[@]}" )
    else
        selected_sections=( $section )
    fi

    [ ${#selected_sections[*]} -eq 0 ] && return

    note_count="$(psql -U milestone -d milestone -c "select count(id) from notes where section_id in ( $(tr ' ' ',' <<< "${selected_sections[*]}") )" -At)"
    note_number=0

    while IFS="|" read -r section section_name section_state
    do
        echo -e "\e[1;35m$id\e[0m \e[1;36m$name\e[0m \e[2;37m($state)\e[0m"
        while IFS="|" read -r note state heading
        do
            note_number=$((note_number + 1))
            notes[$note]="$parent"
            heading="$(pandoc -f markdown -t plain <<< "$heading" | xargs)"

            clear
            printf "\e[1;36m%s\e[0m \e[2;37m%d\e[0m \e[1;33m>>\e[0m \e[1;36m%s\e[0m \e[2;37m%d (%s)\e[0m\n\n" "${resources[$resource]}" ${resource} "$section_name" ${section} "$section_state"
            printf "\e[1;35m%d/%d\e[0m \e[1;33m%s\e[0m \e[2;37m%s (%s)\e[0m\n" $note_number $note_count "$heading" $note "$state"

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
                tput cup $last_line $(($(tput cols) - 28))
                tput civis
                echo -ne "\e[1;31mPress [N]ext to move forward\e[0m"
                read -n 1 -s response </dev/tty
                tput cnorm
                [[ "${response,,}" == "n" ]] && break
            done
        done < <(psql -U milestone -d milestone -c "select id, state, heading from notes where section_id = $section" -At)
    done < <(psql -U milestone -d milestone -c "select id, number, state from sections where id in ( $(tr ' ' ',' <<< "${selected_sections[*]}") ) order by number, created" -At)
    echo
}

case "${mode,,}" in
    s|study) start_study ;;
    p|practice) start_practice ;;
    *) echo -e "\e[1;31mIncorrect mode selected\e[0m" ;;
esac
