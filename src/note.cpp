#include <flashback/note.hpp>

using namespace flashback;

note::note(unsigned long int const id):
    _id{id}, _title{}, _description{}, _position{}, _collected{false}, _collectable{true}
{
}

unsigned long int note::id() const
{
    return _id;
}

std::string note::title() const
{
    return _title;
}

void note::title(std::string const& title)
{
    _title = title;
}

void note::title(std::string&& title) noexcept
{
    _title = std::move(title);
}

std::string note::description() const
{
    return _description;
}

void note::description(std::string const& description)
{
    _description = description;
}

void note::description(std::string&& description) noexcept
{
    _description = std::move(description);
}

std::string note::position() const
{
    return _position;
}

void note::position(std::string const& position)
{
    _position = position;
}

void note::position(std::string&& position) noexcept
{
    _position = std::move(position);
}

bool note::collected() const
{
    return _collected;
}

void note::collected(bool const collected)
{
    _collected = collected;
}

bool note::collectable() const
{
    return _collectable;
}

void note::collectable(bool const collectable)
{
    _collectable = collectable;
}

bool note::operator<(note const& other)
{
    return _position < other._position;
}

bool note::operator!=(note const& other)
{
    return _id != other.id();
}
