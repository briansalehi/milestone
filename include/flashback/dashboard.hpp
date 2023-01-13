#pragma once

#include <flashback/argument_parser.hpp>
#include <flashback/loader.hpp>
#include <flashback/space.hpp>
#include <flashback/library.hpp>
#include <flashback/trainer.hpp>

#include <string_view>
#include <string>
#include <vector>
#include <array>

namespace flashback
{
class dashboard
{
public:
    dashboard();

    constexpr std::vector<std::string> space_names() const;

    void open();

private:
    std::shared_ptr<space> build_space(std::string_view);

    std::string prompt_space() const;

    void enter_space();

private:
    std::shared_ptr<space> _active_space;
};

} // flashback
