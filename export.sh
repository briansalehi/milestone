#!/usr/bin/env bash

while IFS="|" read -r m_resource resource_name m_resource_type m_resource_pattern m_author
do
    case "$m_resource_type" in
        unknown) f_resource_type="book" ;;
        *) f_resource_type="$m_resource_type" ;;
    esac

    f_resource_pattern="${m_resource_pattern,,}"

    #f_resource=$(psql -U flashback -d flashback -c "select create_resource('$resource_name', '$f_resource_type'::resource_type, '$f_resource_pattern'::section_pattern, '$author', '')" -At)

    printf "\e[1;36mresource\e[0m: \e[1;36mtype\e[0m %-12s / \e[1;36mpattern\e[0m %-6s / \e[1;36mauthor\e[0m %s / \e[1;36mname\e[0m %s\n" "$f_resource_type" "$f_resource_pattern" "$author" "$resource_name"

    while IFS="|" read -r m_section m_section_position
    do
        f_section_position=$m_section_position

        psql -U flashback -d flashback -c "select create_section($f_resource, $f_section_position, '')" -At

        printf "  \e[1;33msection\e[0m %-4s / \e[1;33mposition\e[0m %-2s\n" "$m_section" "$m_section_position"
    done < <(psql -U milestone -d milestone -c "select id, number from sections where resource_id = $m_resource order by number" -At)
done < <(psql -U milestone -d milestone -c "select id, name, type, section_pattern_id, leading_author from resources order by id" -At)

#resources:
#  id (internal)
#  name
#  type:
#    resource_type:
#      - unknown
#        book
#        website
#        course
#        video
#        mailing list
#        manual
#        slides
#    resource_type:
#      - book
#        website
#        course
#        video
#        mailing list
#        manual
#        slides
#  pattern:
#    section_pattern_id:
#      - Chapter
#        Page
#        Course
#        Video
#        Post
#    section_pattern:
#      - chapter
#        page
#        course
#        video
#        post
#  condition:
#    - draft
#      relevant (default)
#      outdated
#      canonical
#      abandoned
#  leading_author
#  sections:
#    id (internal):
#      integer
#      resource
#    number:
#      integer
#      position
#    name:
#      string:
#        - null
#cards:
#  notes:
#    id (internal)
#    heading
#    state:
#      publication_state:
#        - open
#          writing
#          completed
#          revised
#          validated
#          approved
#          released
#          ignored
#      card_state:
#        - draft
#          review
#          approved
#          completed
#          rejected
#sections_cards:
#  notes:
#    number
#    position
#blocks:
#  note_blocks:
#    id (internal)
#  position
#  content
#  type:
#    block_type:
#      - text
#        code
#    content_type:
#      - text
#        code
#    extension:
#      language
#      extension

