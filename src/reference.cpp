#include <flashback/reference.hpp>

using namespace flashback;

std::string reference::title() const
{
    return _title;
}

void reference::title(std::string const& title)
{
    _title = title;
}

void reference::title(std::string&& title)
{
    _title = std::move(title);
}

std::string reference::value() const
{
    return _value;
}

void reference::value(std::string const& value)
{
    _value = value;
}

void reference::value(std::string&& value)
{
    _value = std::move(value);
}
