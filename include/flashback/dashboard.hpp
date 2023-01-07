#pragma once

#include <flashback/argument_parser.hpp>
#include <flashback/loader.hpp>

#include <string_view>
#include <string>
#include <vector>

namespace flashback
{
enum class space {library, trainer, tutorials, roadmap};

class dashboard
{
public:

    explicit dashboard(std::string const&);

    constexpr std::vector<std::string> spaces() const;

    space prompt() const;

private:
    space get_space(std::string const&) const;

    void enter_space(space const);
};

} // flashback
