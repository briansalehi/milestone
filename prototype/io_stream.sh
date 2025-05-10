#!/usr/bin/env bash

write_header()
{
    local header="$*"
    printf "\n\e[1;36m%-s\n\e[9m%-*.s\e[0m\n\n" "${header}" ${#header}
}

write_block()
{
    local type="$1"
    shift
    local content="$@"

    case "$type" in
        text)
            printf "\e[1;2;37m%-80.*s\n" ${#content} "${content}"
            ;;
        code)
            temp_file="$(mktemp)"
            echo "$content" > "$temp_file"
            bat --wrap auto --paging never --squeeze-blank --style numbers,grid --language cpp --file-name "basic_type.cpp" "$temp_file"
            rm "$temp_file"
            ;;
    esac
    echo -e "\e[0m"
}
