#!/usr/bin/env bash

global_resources_count=0
global_sections_count=0
global_subjects_count=0
global_topics_count=0
global_cards_count=0
global_blocks_count=0

show_progress()
{
    local increment_resources="${1:-0}"
    local increment_sections="${2:-0}"
    local increment_subjects="${3:-0}"
    local increment_topics="${4:-0}"
    local increment_cards="${5:-0}"
    local increment_blocks="${6:-0}"

    [ $increment_resources -eq 1 ] && global_resources_count=$((global_resources_count + 1))
    [ $increment_sections -eq 1 ]  && global_sections_count=$((global_sections_count + 1))
    [ $increment_subjects -eq 1 ]  && global_subjects_count=$((global_subjects_count + 1))
    [ $increment_topics -eq 1 ]    && global_topics_count=$((global_topics_count + 1))
    [ $increment_cards -eq 1 ]     && global_cards_count=$((global_cards_count + 1))
    [ $increment_blocks -eq 1 ]    && global_blocks_count=$((global_blocks_count + 1))

    printf "\rresources: %-5d sections: %-5d subjects: %-5d topics: %-5d cards: %-5d blocks: %-5d" $global_resources_count $global_sections_count $global_subjects_count $global_topics_count $global_cards_count $global_blocks_count
}

export_resources()
{
    while IFS="|" read -r m_resource resource_name m_resource_type m_resource_pattern author
    do
        case "$m_resource_type" in
            unknown) f_resource_type="book" ;;
            *) f_resource_type="$m_resource_type" ;;
        esac

        case "$m_resource_pattern" in
            1) f_resource_pattern="chapter";;
            2) f_resource_pattern="page";;
            3) f_resource_pattern="course";;
            4) f_resource_pattern="video";;
            5) f_resource_pattern="post";;
            *) f_resource_pattern="chapter";;
        esac

        f_resource=$(psql -U flashback -d flashback -c "select create_resource('${resource_name//\'/\'\'}', '${f_resource_type//\'/\'\'}'::resource_type, '${f_resource_pattern//\'/\'\'}'::section_pattern, '${author//\'/\'\'}', '')" -At) || break

        show_progress 1 0 0 0 0 0

        while IFS="|" read -r m_section m_section_position
        do
            f_section_position=$m_section_position

            section=$(psql -U flashback -d flashback -c "select create_section(${f_resource//\'/\'\'}, ${f_section_position//\'/\'\'}, '')" -At) || break

            show_progress 0 1 0 0 0 0

            backup_position=0

            while IFS="|" read -r note note_state note_position heading
            do
                case "$note_state" in
                    open|writing) card_state="draft" ;;
                    completed|revised) card_state="review" ;;
                    approved|validated) card_state="approved" ;;
                    released) card_state="completed" ;;
                    ignored) card_state="rejected" ;;
                    *) card_state="draft" ;;
                esac

                backup_position=$((backup_position + 1))

                card_position=$note_position

                if [ $card_position -eq 0 ]
                then
                    card_position=$backup_position
                fi

                card=$(psql -U flashback -d flashback -c "select create_card('${card_state}', '${heading//\'/\'\'}')" -At) || break
                result=$(psql -U flashback -d flashback -c "select add_card_to_section(${f_resource}, ${f_section_position}, ${card}, ${card_position})" -At)

                show_progress 0 0 0 0 1 0

                while IFS="|" read -r m_block block_position content_type extension
                do
                    content="$(psql -U milestone -d milestone -c "select content from note_blocks where id = ${m_block}" -At)"

                    block=$(psql -U flashback -d flashback -c "select create_block(${card//\'/\'\'}, ${block_position//\'/\'\'}, '${content_type//\'/\'\'}'::content_type, '${extension//\'/\'\'}', '${content//\'/\'\'}')" -At) || break

                    show_progress 0 0 0 0 0 1
                done < <(psql -U milestone -d milestone -c "select id, position, type, language from note_blocks where note_id = $note order by position, id" -At)
            done < <(psql -U milestone -d milestone -c "select id, state, number, heading from notes where section_id = $m_section order by number, id" -At)
        done < <(psql -U milestone -d milestone -c "select id, number from sections where resource_id = $m_resource order by number" -At)
    done < <(psql -U milestone -d milestone -c "select id, name, type, section_pattern_id, leading_author from resources order by id" -At)
    echo
}

export_subjects()
{
    while IFS="|" read -r m_subject subject_name
    do
        f_subject=$(psql -U flashback -d flashback -c "select create_subject('${subject_name//\'/\'\'}')" -At) || break

        show_progress 0 0 1 0 0 0

        while IFS="|" read -r m_topic topic_position topic_name
        do
            result=$(psql -U flashback -d flashback -c "select create_topic(${f_subject//\'/\'\'}, 'surface'::expertise_level, ${topic_position//\'/\'\'}, '$topic_name')" -At) || break

            show_progress 0 0 0 1 0 0

            backup_position=0

            while IFS="|" read -r practice practice_position heading
            do
                card_state="draft"
                card_position=$practice_position
                backup_position=$((backup_position + 1))

                [ $card_position -eq 0 ] && card_position=$backup_position

                card=$(psql -U flashback -d flashback -c "select create_card('${card_state}', '${heading//\'/\'\'}')" -At) || break
                result=$(psql -U flashback -d flashback -c "select add_card_to_topic(${f_subject}, 'surface'::expertise_level, ${topic_position}, ${card}, ${card_position})" -At)

                show_progress 0 0 0 0 1 0

                while IFS="|" read -r m_block block_position content_type extension
                do
                    content="$(psql -U milestone -d milestone -c "select content from practice_blocks where id = ${m_block}" -At)"

                    block=$(psql -U flashback -d flashback -c "select create_block(${card//\'/\'\'}, ${block_position//\'/\'\'}, '${content_type//\'/\'\'}'::content_type, '${extension//\'/\'\'}', '${content//\'/\'\'}')" -At) || break

                    show_progress 0 0 0 0 0 1
                done < <(psql -U milestone -d milestone -c "select id, position, type, language from practice_blocks where practice_id = $practice order by position, id" -At)
            done < <(psql -U milestone -d milestone -c "select id, position, heading from practices where topic_id = $m_topic order by position, id" -At)
        done < <(psql -U milestone -d milestone -c "select id, position, name from topics where subject_id = $m_subject order by position" -At)
        read pause </dev/tty
    done < <(psql -U milestone -d milestone -c "select id, name from subjects order by id" -At)
    echo
}

#export_resources
export_subjects
