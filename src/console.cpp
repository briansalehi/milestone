#include <flashback/console.hpp>

using namespace flashback;

console::console(std::ostream& output, std::istream& input):
    _output{output},
    _input{input}
{
}

void console::write(std::string_view text, console::color const color, bool const newline)
{
    brush color_brush{color};
    _output << text << (newline ? "\n" : " ");
}

bool console::read_bool(std::string_view text, console::color const color)
{
    brush color_brush{color};
    char buffer{};

    _output << text << "? (N/y) ";
    _input >> buffer;

    return buffer == 'y' ? true : false;
}

std::string console::read_string()
{
    std::string buffer;
    _input >> buffer;

    if (_input.eof())
        throw std::runtime_error("operation cancelled");

    return buffer;
}

std::size_t console::read_size()
{
    std::string buffer;

    _input >> buffer;

    if (_input.eof())
        throw std::runtime_error("operation cancelled");

    std::size_t size{std::stoul(buffer)};
    
    return size;
}

std::string console::read_string(std::string_view prompt, console::color color)
{
    brush color_brush{color};
    std::string buffer;

    _output << prompt << ": ";
    _input >> buffer;

    if (_input.eof())
        throw std::runtime_error("operation cancelled");

    return buffer;
}

std::size_t console::read_size(std::string_view prompt, console::color color)
{
    brush color_brush{color};
    std::size_t size{};

    _output << prompt << ": ";

    _input >> size;

    if (_input.eof())
        throw std::runtime_error("operation cancelled");

    return size;
}

void console::clear()
{
    _output << "\e[2J\e[1;1H";
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
            color_code = "\e[1;34m";
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
            color_code = "\e[1;35m";
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
