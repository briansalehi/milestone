#include <flashback/markdown_book_builder.hpp>
#include <flashback/markdown_note_builder.hpp>
#include <flashback/book.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

markdown_book_builder::markdown_book_builder(std::filesystem::path const& resource_path):
    _resource{std::make_shared<book>()},
    _buffer{resource_path}
{
    if (!_buffer.is_open())
        throw std::runtime_error("cannot open resource file "s + resource_path.string());
}

markdown_book_builder::~markdown_book_builder()
{
    if (_buffer.is_open())
        _buffer.close();
}

void markdown_book_builder::reset()
{
    try
    {
        _resource.reset(new book{});
    }
    catch (std::bad_alloc const& exp)
    {
        _resource.reset();
        _resource = nullptr;
    }
}

std::shared_ptr<resource> markdown_book_builder::result() const
{
    return _resource;
}

void markdown_book_builder::read_title()
{
    std::string title;
    std::getline(_buffer, title);

    std::regex pattern{R"(# \[(.*)\]\(.*\))"s};
    std::smatch matches;
    
    if (std::regex_match(title, matches, pattern))
        _resource->title(std::move(matches[1]));
    else
        throw std::runtime_error("book title could not be found at first line: "s + title);
}

void markdown_book_builder::read_chapters()
{
    std::regex pattern{R"(## (Chapter\s)(\d+)\s*\/\s*(\d+))"s};
    std::smatch matches;
    std::string position;
    std::string line;

    std::getline(_buffer, line);

    while (!std::regex_match(line, matches, pattern))
    {
        if (_buffer.eof())
            return;

        std::getline(_buffer, line);
    }

    dynamic_cast<book*>(_resource.get())->chapters(std::stoi(matches[3]));
    position = matches[1].str() + matches[2].str();

    while (std::getline(_buffer, line))
    {
        if (line == "<details>")
        {
            read_note(position);
        }
        else if (std::regex_match(line, matches, pattern))
        {
            position = matches[1].str() + matches[2].str();
        }
    }
}

void markdown_book_builder::read_note(std::string const& position)
{
    markdown_note_builder note_builder{_buffer};

    note_builder.read_title();
    note_builder.read_description();
    note_builder.result()->position(position);
    _resource->add_note(note_builder.result());
}
