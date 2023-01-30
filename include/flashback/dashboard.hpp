#pragma once

#include <flashback/argument_parser.hpp>
#include <flashback/library.hpp>
#include <flashback/trainer.hpp>
#include <flashback/console.hpp>
#include <flashback/loader.hpp>
#include <flashback/space.hpp>

#include <string_view>
#include <string>
#include <vector>
#include <array>

namespace flashback
{
class dashboard
{
public:
    using color = console<std::istream, std::ostream>::color;
    using style = console<std::istream, std::ostream>::style;

    dashboard();

    constexpr std::vector<std::string> space_names() const;

    void open();

private:
    std::shared_ptr<space> build_space(char);

    char prompt_space();

    void enter_space(std::shared_ptr<space>);

private:
    console<std::istream, std::ostream> _stream;
};

} // flashback
