#pragma once

#include <string>

namespace flashback
{

struct note
{
    std::string title;
    std::string description;
    std::string position;
    bool collected;

    bool operator<(note const&);
    bool operator!=(note const&);
};

} // flashback
