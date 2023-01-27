#include <flashback/note.hpp>
#include <flashback/book.hpp>

using namespace flashback;

book::book(std::string const& name, unsigned int const chapters)
    : _title{name}, _chapters{chapters}, _notes{}
{
}

book::book(book const& other)
{
    if (&other != this)
    {
        _title = other._title;
        _notes = other._notes;
        _chapters = other._chapters;
    }
}

book::book(book&& other) noexcept
{
    if (&other != this)
    {
        _title = other._title;
        other._title.clear();
        _notes = other._notes;
        other._notes.clear();
        _chapters = other._chapters;
        other._chapters = 0;
    }
}

book& book::operator=(book const& other)
{
    if (&other != this)
    {
        _title = other._title;
        _notes = other._notes;
        _chapters = other._chapters;
    }

    return *this;
}

book& book::operator=(book&& other) noexcept
{
    if (&other != this)
    {
        _title = other._title;
        other._title.clear();
        _notes = other._notes;
        other._notes.clear();
        _chapters = other._chapters;
        other._chapters = 0;
    }

    return *this;
}

std::string book::name() const
{
    return _title;
}

void book::name(std::string const& name)
{
    _title = name;
}

void book::name(std::string&& name) noexcept
{
    _title = std::move(name);
}

std::shared_ptr<note> book::take_note(std::size_t const index) const
{
    return _notes.at(index);
}

std::vector<std::shared_ptr<note>> book::notes() const
{
    return _notes;
}

bool book::add_note(std::shared_ptr<note> note)
{
    bool status = false;

    if (note)
    {
        _notes.push_back(note);
        status = true;
    }

    return status;
}

unsigned int book::chapters() const
{
    return _chapters;
}

void book::chapters(unsigned int const chapters)
{
    _chapters = chapters;
}
