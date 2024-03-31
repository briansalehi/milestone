#include <flashback/flashcard.hpp>

namespace flashback
{

flashcard::flashcard(std::ostringstream const& buffer)
{
}

flashcard::flashcard(flashcard const& other)
{
}

flashcard& flashcard::operator=(flashcard const& other)
{
}

flashcard::flashcard(flashcard&& other)
{
}

flashcard& flashcard::operator=(flashcard&& other)
{
}

flashcard::~flashcard()
{
}

void flashcard::parse_stream()
{
    std::string line;

    while (stream >> line)
    {
    }
}

} // flashback
