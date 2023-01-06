#include <flashback/markdown_resource_builder.hpp>
#include <flashback/markdown_note_builder.hpp>
#include <flashback/book.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

markdown_resource_builder::markdown_resource_builder():
    _resource{std::make_shared<book>()}
{
}

void markdown_resource_builder::reset()
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

std::shared_ptr<resource> markdown_resource_builder::result() const
{
    return _resource;
}

void markdown_resource_builder::read_title(std::stringstream& buffer) const
{
    ///
    /// When `<details>` is read, either of these cases are possible:
    ///
    /// 1. First practice hit, because reference scope is not open.
    /// 2. Next practice hit because reference scope is open from the previous note.
    ///
    std::string title;
    std::getline(buffer, title);

    std::regex pattern{R"(# \[(.*)\]\(.*\))"s};
    std::smatch matches;
    
    if (std::regex_match(title, matches, pattern))
        _resource->title(std::move(matches[1]));
    else
        throw std::runtime_error("book title could not be found at first line"s);
}

void markdown_resource_builder::read_chapters(std::stringstream& buffer) const
{
    ///
    /// When `## Chapter N/M` is read, either of these cases are possible:
    ///
    /// 1. First chapter begins, because no chapter scope is open.
    /// 2. Next chapter hit, because chapter scope is already open from the previous one.
    ///
    std::regex pattern{R"(## Chapter (\d)\s*\/\s*(\d))"s};
    std::smatch matches;
    std::string line;

    std::getline(buffer, line);

    while (!std::regex_match(line, matches, pattern))
    {
        std::getline(buffer, line);
        std::cerr << line << "\n";
    }

    dynamic_cast<book*>(_resource.get())->chapters(std::stoi(matches[2]));

    while (buffer.good())
        read_note(buffer);
}

void markdown_resource_builder::read_note(std::stringstream& buffer) const
{
    markdown_note_builder note_builder{};

    std::string line;
    std::getline(buffer, line);

    if (line == "<details>")
    {
        note_builder.read_title(buffer);
        note_builder.read_description(buffer);
        //note_builder.read_references(buffer);
        _resource->add_note(note_builder.result());
        note_builder.reset();
    }
}
