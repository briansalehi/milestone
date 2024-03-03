#include <flashback/flashcard.hpp>

#include <exception>
#include <algorithm>
#include <utility>

namespace flashback
{

flashcard::flashcard(std::stringstream& buffer)
{
    parse_stream(buffer);
}

flashcard::flashcard(flashcard const& card)
    : title{card.title}
    , body{card.body}
{
    std::copy(card.resources.begin(), card.resources.end(), resources.begin());
    std::copy(card.references.begin(), card.references.end(), references.begin());
}

flashcard& flashcard::operator=(flashcard const& card)
{
    title = card.title;
    body = card.body;
    std::copy(card.resources.begin(), card.resources.end(), resources.begin());
    std::copy(card.references.begin(), card.references.end(), references.begin());
    return *this;
}

flashcard::flashcard(flashcard&& card) noexcept
    : title{std::move(card.title)}
    , body{std::move(card.body)}
{
    std::move(card.resources.begin(), card.resources.end(), resources.begin());
    std::move(card.references.begin(), card.references.end(), references.begin());
}

flashcard& flashcard::operator=(flashcard&& card) noexcept
{
    title = std::move(card.title);
    body = std::move(card.body);
    std::move(card.resources.begin(), card.resources.end(), resources.begin());
    std::move(card.references.begin(), card.references.end(), references.begin());
    return *this;
}

void flashcard::parse_stream(std::stringstream& buffer)
{
    std::string line;
    std::getline(buffer, line);
    if (line != R"(<details>)")
    {
        std::string description{"invalid beginning of flashcard, expected <details> got "};
        throw std::runtime_error{description + line};
    }

    std::getline(buffer, line);
    parse_title(line);

    /*
    std::getline(buffer, line);
    if (line != R"(</details>)")
    {
        std::string description{"invalid ending of flashcard, expected </details> got "};
        throw std::runtime_error{description + line};
    }
    */
}

void flashcard::parse_title(std::string const& line)
{
    std::string::size_type beg_position = line.find("<summary>");
    std::string::size_type end_position = line.find("</summary>");

    if ((beg_position == std::string::npos) && (end_position == std::string::npos))
        throw std::runtime_error("summary tag not found where expected: " + line);
    else if (beg_position == std::string::npos)
        throw std::runtime_error("no opening summary tag found: " + line);
    else if (end_position == std::string::npos)
        throw std::runtime_error("no closing summary tag found: " + line);
    else if (beg_position != 0)
        std::cerr << std::format("{}\n", "line not beginning with summary tag: " + std::string{line.begin(), line.begin() + beg_position});

    std::string::size_type title_begin_pos = line.find_first_not_of("<summary>");

    title = std::string{line.begin() + title_begin_pos, line.begin() + end_position};
}

void flashcard::parse_body(std::stringstream& buffer)
{
    std::string line;
    std::getline(buffer, line);

    if (!line.empty())
        throw std::runtime_error{"empty line after summary is missing: " + line};

    char next{};
    while ((next = buffer.peek()) == '>')
    {
        std::getline(buffer, line);
    }
}

void flashcard::parse_resources(std::stringstream& buffer)
{
}

void flashcard::parse_references(std::stringstream& buffer)
{
}

} // flashback
