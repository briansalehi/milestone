#pragma once

#include <string_view>
#include <iostream>
#include <string>

namespace flashback
{

class console
{
public:
    enum class color {reset,red,blue,green,orange,pink,white,darkred};

    explicit console(std::ostream&, std::istream&);

    void write(std::string_view, color const = color::reset, bool const = true);

    std::string read_string();
    std::string read_string(std::string_view, color);

    bool read_bool(std::string_view, color);

    std::size_t read_size();
    std::size_t read_size(std::string_view, color);

    void clear();

private:
    struct brush
    {
        explicit brush(color const);
        virtual ~brush();
    };

private:
    std::ostream& _output;
    std::istream& _input;
};

} // flashback
