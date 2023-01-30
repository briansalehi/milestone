#include <flashback/console.hpp>

using namespace flashback;

/*
template <typename I, typename O>
console<I, O>::console(I& input, O& output): _input{input}, _output{output}
{
}

template <typename I, typename O>
void console<I, O>::clear()
{
    _output << "\e[2J\e[1;1H";
}

template <typename I, typename O>
template <typename T>
void console<I, O>::header(T const& printable_object)
{
    _output << style::reverse;
    _output.width(90);
    _output << printable_object;
}

template <typename I, typename O>
template <typename T>
console<I, O>& console<I, O>::operator>>(T const& writable_object)
{
    _input >> writable_object;

    return *this;
}

template <typename I, typename O>
template <typename T>
console<I, O>& console<I, O>::operator<<(T const& printable_object)
{
    _output << printable_object; 

    return *this;
}

template <typename I, typename O>
console<I, O>& console<I, O>::operator<<(console<I, O>::color const picked_color)
{
    std::string color_code{};

    switch (picked_color)
    {
        case color::reset:      color_code = "\e[0m";
        case color::red:        color_code = "\e[31m";
        case color::green:      color_code = "\e[32m";
        case color::orange:     color_code = "\e[33m";
        case color::blue:       color_code = "\e[34m";
        case color::pink:       color_code = "\e[35m";
        case color::cyan:       color_code = "\e[36m";
        case color::white:      color_code = "\e[37m";
        case color::gray:       color_code = "\e[38m";
        default:                color_code = "\e[0m";
    }

    _output << color_code;

    return *this;
}

template <typename I, typename O>
console<I, O>& console<I, O>::operator<<(console<I, O>::style const picked_style)
{
    std::string style_code;

    switch (picked_style)
    {
        case style::newline:    style_code = "\n";
        case style::bold:       style_code = "\e[1m";
        case style::dim:        style_code = "\e[2m";
        case style::italic:     style_code = "\e[3m";
        case style::underline:  style_code = "\e[4m";
        case style::blink:      style_code = "\e[5m";
        case style::reverse:    style_code = "\e[7m";
        case style::strike:     style_code = "\e[9m";
        default:                style_code = "\e[0m";
    }
    _output << style_code;

    return *this;
}
*/
