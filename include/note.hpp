#pragma once

#include <string>

namespace flashback
{

struct note
{
    bool collected;
    std::string title;
    std::string description;
    std::string position;

    bool operator<(note const&);
    bool operator!=(note const&);
};

} // flashback
