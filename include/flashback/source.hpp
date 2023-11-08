#pragma once

#include <string>
#include <compare>

namespace flashback
{

class source
{
public:
    source(std::string const&);

    auto operator<=>(source const&) = default;

private:
    std::string _title;
};

} // flashback
