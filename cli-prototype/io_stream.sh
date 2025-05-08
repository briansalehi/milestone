#!/usr/bin/env bash

write_header()
{
    local header="  $*  "
    local max_width=$(tput cols)

    if [ ${#header} -lt ${max_width} ]
    then
        max_width=${#header}
    fi

    printf "\e[0m\e[1;7;36m%*.s\n" ${max_width}
    echo "$header"
    printf "%*.s\e[0m\n" ${max_width}
}

write_block()
{
    local type="$1"
    shift
    local content="$@"

    case "$type" in
        text)
            echo -e "\e[0m\e[2;37m"
            echo "$@"
            ;;
        code)
            temp_file="$(mktemp)"
            echo "$@" > "$temp_file"
            bat --wrap auto --language cpp --file-name "basic_type.cpp" "$temp_file"
            rm "$temp_file"
            ;;
    esac
    echo -e "\e[0m"
}
