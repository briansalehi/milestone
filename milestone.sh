#!/usr/bin/env bash

trap 'printf "\r\e[1;31m%-*s\e[0m" $(tput cols) "User Interrupted"; tput cnorm; exit 1' SIGINT

read -n 1 -p "Do you want to [P]ractice or [S]tudy? " mode
echo
echo

last_line=$(($(tput lines) - 2))
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

show_blocks()
{
    local card="$1"

    while IFS="|" read -r block type extension
    do
        content="$(psql -U flashback -d flashback -c "select content from blocks where card = $card and position = $block" -At)"

        printf "\e[2;37m%*s\e[0m" $(tput cols) "$type $extension $block"
        case "$type" in
            text) echo "$content" | bat --paging never --squeeze-blank --language "md" --style "plain" ;;
            code) echo "$content" | bat --paging never --squeeze-blank --language "$extension" --style "grid,numbers" ;;
            *) echo -e "\e[1;31mInvalid block type and extension $type / $extension" ;;
        esac
        echo
    done < <(psql -U flashback -d flashback -c "select position, type, extension from blocks where card = $card order by position" -At)
}

start_practice()
{
    local -A subjects
    local -A topics

    while IFS='|' read -r id name
    do
        subjects[$id]="$name"
    done < <(psql -U flashback -d flashback -c "select id, name from subjects order by id" -At)

    clear
    while IFS='|' read -r id name topic_count
    do
        printf "\e[1;35m%5d\e[0m \e[1;36m%s\e[0m \e[2;37m(%d)\e[0m\n" $id "$name" $topic_count
    done < <(psql -U flashback -d flashback -c "select s.id, s.name, count(t.position) from subjects s left join topics t on t.subject = s.id group by s.id, s.name order by id" -At) | dense_column

    while true
    do
        echo
        read -p "Select a subject: " subject
        [[ -n "${subjects[$subject]}" ]] && break
    done

    subject_name="${subjects[$subject]}"

    while IFS="|" read -r id name
    do
        topics[$id]="$name"
    done < <(psql -U flashback -d flashback -c "select position, name from topics where subject = $subject order by position" -At)

    clear
    printf "\e[1;36m%s\e[0m \e[2;37m%d\e[0m\n\n" "${subject_name}" ${subject}
    while IFS="|" read -r id name
    do
        echo -e "\e[1;35m$id\e[0m \e[1;36m$name\e[0m"
    done < <(psql -U flashback -d flashback -c "select position, name from topics where subject = $subject order by position" -At) | dense_column

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

    while IFS="|" read -r topic level topic_name
    do
        while IFS="|" read -r card state position heading
        do
            heading="$(pandoc -f markdown -t plain <<< "$heading" | xargs)"
            practice_count="$(psql -U flashback -d flashback -c "select count(card) from topics_cards where subject = $subject and topic = $topic" -At)"

            clear
            printf "\e[1;36m%s\e[0m \e[2;37m%d\e[0m \e[1;33m>>\e[0m \e[1;36m%s\e[0m \e[2;37m%d / %d\e[0m\n\n" "${subject_name}" ${subject} "$topic_name" ${topic} ${#topics[*]}
            printf "\e[1;35m%d/%d\e[0m \e[1;33m%s\e[0m \e[2;37m(%s)\e[0m \e[2;37m%s\e[0m\n" $position $practice_count "$heading" "$state" $card

            show_blocks $card

            while true
            do
                tput cup $last_line $(($(tput cols) - 28))
                tput civis
                echo -ne "\e[1;31mPress [N]ext to move forward\e[0m"
                read -n 1 -s response </dev/tty
                tput cnorm
                [[ "${response,,}" == "n" ]] && break
            done
        done < <(psql -U flashback -d flashback -c "select c.id, c.state, t.position, c.heading from topics_cards t join cards c on c.id = t.card where t.subject = $subject and t.level = '$level' and t.topic = $topic" -At)
    done < <(psql -U flashback -d flashback -c "select position, level, name from topics where subject = $subject and position in ( $(tr ' ' ',' <<< "${selected_topics[*]}") ) order by position" -At)
    echo
}

start_study()
{
    local -A resources
    local -A sections

    while IFS='|' read -r id name
    do
        resources[$id]="$name"
    done < <(psql -U flashback -d flashback -c "select id, name from resources order by name" -At)

    clear
    while IFS='|' read -r id name section_count
    do
        printf "\e[1;35m%5d\e[0m \e[1;36m%s\e[0m \e[2;37m(%d)\e[0m\n" $id "$name" $section_count
    done < <(psql -U flashback -d flashback -c "select r.id, r.name, count(s.position) from resources r left join sections s on s.resource = r.id group by r.id, r.name order by name" -At) | dense_column

    while true
    do
        read -p "Select a resource: " resource
        [[ -n "${resources[$resource]}" ]] && break
    done

    clear
    printf "\e[1;36m%s\e[0m \e[2;37m%d\e[0m\n\n" "${resources[$resource]}" ${resource}
    while IFS="|" read -r position name pattern
    do
        sections[$position]="${pattern^} ${name:-$position}"
    done < <(psql -U flashback -d flashback -c "select s.position, s.name, r.pattern from resources r join sections s on s.resource = r.id where r.id = $resource order by s.position" -At)

    while IFS="|" read -r position name pattern
    do
        echo -e "\e[1;35m$position\e[0m \e[1;36m${pattern^} ${name:-$position}\e[0m"
    done < <(psql -U flashback -d flashback -c "select s.position, s.name, r.pattern from resources r join sections s on r.id = s.resource where r.id = $resource order by s.position" -At) | dense_column

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

    note_number=0

    while IFS="|" read -r resource_name resource_type pattern condition author publisher
    do
        while IFS="|" read -r section section_position
        do
            echo -e "\e[1;35m$id\e[0m \e[1;36m$name\e[0m \e[2;37m($state)\e[0m"
            while IFS="|" read -r card state position heading
            do
                note_number=$((note_number + 1))
                heading="$(pandoc -f markdown -t plain <<< "$heading" | xargs)"
                note_count="$(psql -U flashback -d flashback -c "select count(card) from sections_cards where resource = $resource and section = $section" -At)"

                clear
                printf "\e[1;36m%s\e[0m presented by \e[1;36m«%s»\e[0m published by \e[1;36m«%s»\e[0m \e[2;37m(%s) %d\e[0m \e[1;33m>>\e[0m \e[1;36m%s\e[0m \e[2;37m%d / %d\e[0m\n\n" "${resource_name}" "${author}" "${publisher}" "${condition}" ${resource} "${pattern^} $section_position" ${section} ${#sections[*]}
                printf "\e[1;35m%d/%d\e[0m \e[1;33m%s\e[0m \e[2;37m%s (%s)\e[0m\n" $note_number $note_count "$heading" $card "$state"

                show_blocks $card

                while true
                do
                    tput cup $last_line $(($(tput cols) - 28))
                    tput civis
                    echo -ne "\e[1;31mPress [N]ext to move forward\e[0m"
                    read -n 1 -s response </dev/tty
                    tput cnorm
                    [[ "${response,,}" == "n" ]] && break
                done
            done < <(psql -U flashback -d flashback -c "select c.id, c.state, t.position, c.heading from sections_cards t join cards c on c.id = t.card where resource = $resource and section = $section" -At)
        done < <(psql -U flashback -d flashback -c "select position, name from sections where resource = $resource and position in ( $(tr ' ' ',' <<< "${selected_sections[*]}") ) order by position" -At)
    done < <(psql -U flashback -d flashback -c "select name, type, pattern, condition, leading_author, publisher from resources where id = $resource" -At)
    echo
}

case "${mode,,}" in
    s|study) start_study ;;
    p|practice) start_practice ;;
    *) echo -e "\e[1;31mIncorrect mode selected\e[0m" ;;
esac
