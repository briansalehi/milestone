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
    parse_body(buffer);
    parse_resources(buffer);
    parse_references(buffer);

    std::getline(buffer, line);
    if (line != R"(</details>)")
    {
        std::string description{"invalid ending of flashcard, expected </details> got "};
        throw std::runtime_error{description + line};
    }
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
        std::cerr << std::format(
            "{}\n", "line not beginning with summary tag: "
            + std::string{line.begin(), line.begin() + beg_position});

    std::string::size_type title_begin_pos = line.find_first_not_of("<summary>");

    title = std::string{line.begin() + title_begin_pos, line.begin() + end_position};
}

void flashcard::parse_body(std::stringstream& buffer)
{
    std::string line{};
    std::ostringstream body_buffer{};
    char first_character_in_line{};

    /*
     * There should be an empty line right after summary tag.
     * Otherwise, browsers will not parse the tags.
     */
    {
        std::getline(buffer, line);

        if (!line.empty())
            throw std::runtime_error{"missing empty line after summary: " + line};
    }

    /*
     * Description heading is optional at the very first line of the body.
     * When exists, it should be ignored. This heading only exists for
     * better visualization of the review.
     * There should be an empty line right after this heading.
     * When empty line found, it is ignored and stored otherwise.
     */
    {
        std::getline(buffer, line);

        if (line == "> **Description**")
        {
            std::getline(buffer, line);

            if (line != ">")
            {
                line.erase(0, 2);
                body_buffer << std::move(line);
            }
        }
    }

    /*
     * Body should contain lines beginning with '> ' and the end
     * of it should be marked with '> ---' which then gives the
     * space to next block of data.
     */
    while ((first_character_in_line = buffer.peek()) == '>')
    {
        std::getline(buffer, line);

        if (line == "> ---")
            break;

        line.erase(0, 2);
        body_buffer << std::move(line) << '\n';
    }

    body = std::move(body_buffer.str());
}

void flashcard::parse_resources(std::stringstream& buffer)
{
    std::string line{};
    char first_character_in_line{};

    std::getline(buffer, line);

    if (line != "> **Resources**")
        throw std::runtime_error{"missing resources heading: " + line};

    while ((first_character_in_line = buffer.peek()) == '>')
    {
        std::getline(buffer, line);

        if (line == "> ---")
            break;

        line.erase(0, 4);
        resources.push_back(std::move(line));
    }
}

void flashcard::parse_references(std::stringstream& buffer)
{
    std::string line{};
    char first_character_in_line{};

    std::getline(buffer, line);

    if (line != "> **References**")
        throw std::runtime_error{"missing references heading: " + line};

    while ((first_character_in_line = buffer.peek()) == '>')
    {
        std::getline(buffer, line);

        if (line == "> ---")
            break;

        line.erase(0, 4);
        references.push_back(std::move(line));
    }
}

} // flashback
