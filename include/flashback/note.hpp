#pragma once

#include <string>
#include <vector>

namespace flashback
{

struct note
{
    std::string title;
    std::string description;
    std::vector<std::string> position;
    bool collected;

    bool operator<(note const&);
    bool operator!=(note const&);
};

} // flashback
