#!/usr/bin/env bash

base="$(dirname "$0")"

source $base/io_stream.sh
source $base/data_types.sh

write_header "What is the role of Single Responsibility in object oriented design?" > "$page_file"

write_block text "This is a short description about Single Responsibility." >> "$page_file"
write_block code "class some_type
{
private:
    std::vector<std::string> data;
public:
    some_type() : data{} { }
}" >> "$page_file"
write_block text "This is another completing description." >> "$page_file"
