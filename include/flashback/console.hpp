#pragma once

#include <string_view>
#include <iostream>
#include <numeric>
#include <iomanip>
#include <string>

namespace flashback
{

template <typename I, typename O>
class console
{
public:
    enum class color {reset, red, blue, green, cyan, orange, pink, white, gray};
    enum class style {bold, italic, dim, underline, blink, reverse, strike, newline};

    /*
    explicit console(I&, O&);

    void clear();

    template <typename T>
    void header(T const&);

    template <typename T>
    console& operator>>(T const& writable_object);

    template <typename T>
    console& operator<<(T const& printable_object);

    console& operator<<(color const picked_color);

    console& operator<<(style const picked_style);
    */

    explicit console(I& input, O& output): _input{input}, _output{output}
    {
    }

    void clear()
    {
        _output << "\e[2J\e[1;1H";
    }

    template <typename T>
    void header(T const& printable_object)
    {
        _output << "\e[7m\e[1m " << std::setw(90);
        _output << std::left << printable_object << "\e[0m\n";
    }

    template <typename T>
    console<I, O>& operator>>(T const& writable_object)
    {
        _input >> writable_object;

        return *this;
    }

    template <typename T>
    console<I, O>& operator<<(T const& printable_object)
    {
        _output << printable_object; 

        return *this;
    }

    console<I, O>& operator<<(color const picked_color)
    {
        std::string color_code{};

        switch (picked_color)
        {
            case color::reset:      color_code = "\e[0m";   break;
            case color::red:        color_code = "\e[31m";  break;
            case color::green:      color_code = "\e[32m";  break;
            case color::orange:     color_code = "\e[33m";  break;
            case color::blue:       color_code = "\e[34m";  break;
            case color::pink:       color_code = "\e[35m";  break;
            case color::cyan:       color_code = "\e[36m";  break;
            case color::white:      color_code = "\e[37m";  break;
            case color::gray:       color_code = "\e[38m";  break;
            default:                color_code = "\e[0m";
        }

        _output << color_code;

        return *this;
    }

    console<I, O>& operator<<(style const picked_style)
    {
        std::string style_code;

        switch (picked_style)
        {
            case style::newline:    style_code = "\n";      break;
            case style::bold:       style_code = "\e[1m";   break;
            case style::dim:        style_code = "\e[2m";   break;
            case style::italic:     style_code = "\e[3m";   break;
            case style::underline:  style_code = "\e[4m";   break;
            case style::blink:      style_code = "\e[5m";   break;
            case style::reverse:    style_code = "\e[7m";   break;
            case style::strike:     style_code = "\e[9m";   break;
            default:                style_code = "\e[0m";
        }
        _output << style_code;

        return *this;
    }

private:
    I& _input;
    O& _output;
};

} // flashback
