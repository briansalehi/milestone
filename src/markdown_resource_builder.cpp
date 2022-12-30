#include <flashback/markdown_resource_builder.hpp>
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

void markdown_resource_builder::read_title(std::stringstream&) const
{
    ///
    /// When `<details>` is read, either of these cases are possible:
    ///
    /// 1. First practice hit, because reference scope is not open.
    /// 2. Next practice hit because reference scope is open from the previous note.
    ///
}

void markdown_resource_builder::read_chapter(std::stringstream&) const
{
    ///
    /// When `## Chapter N/M` is read, either of these cases are possible:
    ///
    /// 1. First chapter begins, because no chapter scope is open.
    /// 2. Next chapter hit, because chapter scope is already open from the previous one.
    ///
}

void markdown_resource_builder::read_note(std::stringstream&) const
{
}
