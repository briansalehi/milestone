#include <flashback/note.hpp>

using namespace flashback;

bool note::operator<(note const& other)
{
    return position < other.position;
}

bool note::operator!=(note const& other)
{
    return position != other.position;
}
