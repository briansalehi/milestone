#include <flashback/markdown_note_builder.hpp>

#include <sstream>
#include <regex>

using namespace flashback;
using namespace std::literals::string_literals;

markdown_note_builder::markdown_note_builder(std::ifstream& data_stream):
    _buffer{data_stream},
    _note{std::make_shared<note>()}
{
    if (!_buffer.is_open())
        throw std::runtime_error("resource not open to extract notes");
}

markdown_note_builder::~markdown_note_builder()
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

void markdown_note_builder::read_title() const
{
    std::string line;
    std::regex pattern{R"(<summary>(.*)</summary>)"s};
    std::smatch matches{};
    std::stringstream title;

    std::getline(_buffer, line);

    if (line == R"(<summary>)"s)
    {
        while (std::getline(_buffer, line))
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

void markdown_note_builder::read_description() const
{
    std::ostringstream body;
    std::string line;

    while (std::getline(_buffer, line))
    {
        if (line == "</details>")
            break;
        else
            body << line << "\n";
    }

    _note->description(body.str());
}

void markdown_note_builder::read_references() const
{
    std::string line;

    /*
    while (std::getline(_buffer, line))
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

    std::getline(_buffer, line);
    _note->position(line);
}

