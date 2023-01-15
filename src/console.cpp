#include <flashback/console.hpp>

using namespace flashback;

console::console(std::ostream& output, std::istream& input):
    _output{output},
    _input{input}
{
}

void console::write(std::string_view text, console::color const color = console::color::reset)
{
    brush color_brush{color};
    _output << text << "\n";
}

std::string console::read_string()
{
    std::string buffer;
    _input >> buffer;
    return buffer;
}

std::size_t console::read_size()
{
    std::size_t size;
    _input >> size;
    return size;
}

std::string console::read_string(std::string_view prompt, console::color color)
{
    brush color_brush{color};
    std::string buffer;
    _output << prompt << ": ";
    _input >> buffer;
    return buffer;
}

std::size_t console::read_size(std::string_view prompt, console::color color)
{
    brush color_brush{color};
    _output << prompt << ": ";
    std::size_t size;
    _input >> size;
    return size;
}

console::brush::brush(console::color const picked_color)
{
    std::string color_code{};

    switch (picked_color)
    {
        case console::color::reset:
        {
            color_code = "\e[0m";
            break;
        }
        case console::color::red:
        {
            color_code = "\e[1;31m";
            break;
        }
        case console::color::blue:
        {
            color_code = "\e[1;35m";
            break;
        }
        case console::color::green:
        {
            color_code = "\e[1;32m";
            break;
        }
        case console::color::orange:
        {
            color_code = "\e[1;33m";
            break;
        }
        case console::color::pink:
        {
            color_code = "\e[1;34m";
            break;
        }
        case console::color::white:
        {
            color_code = "\e[1;37m";
            break;
        }
        case console::color::darkred:
        {
            color_code = "\e[1;27m";
            break;
        }
        default:
        {
            color_code = "\e[0m";
        }
    }

    std::cerr << color_code;
}

console::brush::~brush()
{
    std::cerr << "\e[0m";
}
