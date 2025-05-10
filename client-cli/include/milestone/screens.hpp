#pragma once

#include <ncurses.h>
#include <string>

namespace milestone
{
class screens
{
public:
    explicit screens();
    virtual ~screens();
    void print(int const row, int const column, std::string const& text);

private:
};
} // milestone