#pragma once

#include <flashback/argument_parser.hpp>
#include <flashback/loader.hpp>

namespace flashback
{

class menu
{
public:
    explicit menu(std::string const&);

    constexpr std::vector<std::string> sections() const;

private:
};

} // flashback
