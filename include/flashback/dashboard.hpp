#pragma once

#include <flashback/argument_parser.hpp>
#include <flashback/loader.hpp>

namespace flashback
{
enum class section = {library, trainer, tutorial, roadmap};

class menu
{
public:

    explicit menu(std::string const&);

    constexpr std::vector<std::string> sections() const;

    section prompt(): const;

private:
};

} // flashback
