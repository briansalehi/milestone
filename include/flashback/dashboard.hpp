#pragma once

#include <flashback/argument_parser.hpp>
#include <flashback/loader.hpp>

#include <string_view>
#include <string>
#include <vector>
#include <array>

namespace flashback
{
class dashboard
{
public:
    explicit dashboard(std::string const&);

    constexpr std::vector<std::string> space_names() const;

    std::string prompt() const;

private:
    void enter_space(std::shared_ptr<space> const);

private:
    std::shared_ptr<space_builder> _builder;
    std::array<std::shared_ptr<space>, 4> _spaces;
};

} // flashback
