#pragma once

#include <string>

namespace flashback {

class reference
{
public:
    std::string title() const;
    void title(std::string const&);
    void title(std::string&&);

    std::string value() const;
    void value(std::string const&);
    void value(std::string&&);

private:
    std::string _title;
    std::string _value;
};

} // flashback
