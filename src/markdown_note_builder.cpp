#include <flashback/markdown_note_builder.hpp>

#include <regex>

using namespace flashback;
using namespace std::literals::string_literals;

markdown_note_builder::markdown_note_builder():
    _note{std::make_shared<note>()}
{
}

void markdown_note_builder::reset()
{
    try
    {
        _note.reset(new note{});
    }
    catch (std::bad_alloc const& exp)
    {
        _note.reset();
        _note = nullptr;
    }
}

std::shared_ptr<note> markdown_note_builder::result() const
{
    return _note;
}

void markdown_note_builder::read_title(std::stringstream& buffer) const
{
    std::string line;
    std::regex pattern{R"(<summary>(.*)</summary>)"s};
    std::smatch matches{};
    std::stringstream title;

    std::getline(buffer, line);

    if (line == R"(<summary>)"s)
    {
        while (std::getline(buffer, line))
        {
            if (line == R"(</summary>)"s)
                break;
            else
                title << line;
        }
    }
    else if (std::regex_match(line, matches, pattern))
    {
        title << matches[1];
    }

    _note->title(title.str());
}

void markdown_note_builder::read_description(std::stringstream& buffer) const
{
    std::ostringstream body;
    std::string line;

    while (std::getline(buffer, line))
    {
        if (line == "</details>")
            break;
        else
            body << line;
    }

    _note->description(body.str());
}

void markdown_note_builder::read_references(std::stringstream& buffer) const
{
    std::string line;

    /*
    while (std::getline(buffer, line))
    {
        std::regex pattern{R"(\* \[(.*)\]\((.*)\))"};
        std::smatch matches{};

        if (std::regex_match(line, matches, pattern))
        {
            _note->position(matches[1]);
        }
        else
        {
            break;
        }
    }
    */

    std::getline(buffer, line);
    _note->position(line);
}

