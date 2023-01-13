#include <flashback/book.hpp>
#include <flashback/loader.hpp>
#include <flashback/markdown_book_builder.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

loader::loader(std::filesystem::path const& entities_path):
    _base_path{entities_path}
{
}

loader::~loader()
{
}

std::filesystem::path loader::entities_path() const
{
    return _base_path;
}

std::vector<std::shared_ptr<resource>> loader::resources() const
{
    return _resources;
}

void loader::fetch_content()
{
    auto reader = [this](auto const& entry) { add_resource(entry); };
    std::ranges::for_each(std::filesystem::directory_iterator(_base_path), reader);
}

void loader::add_resource(std::filesystem::path const& entity_path)
{
    if (std::filesystem::is_regular_file(entity_path) && entity_path.extension() == ".md")
    {
        markdown_book_builder builder{entity_path};
        builder.read_title();
        builder.read_chapters();

        _resources.push_back(builder.result());
    }
}
