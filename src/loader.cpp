#include <flashback/book.hpp>
#include <flashback/loader.hpp>
#include <flashback/markdown_book_builder.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

loader::loader(std::filesystem::path const& entities_path):
    _entities_path{entities_path}
{
}

loader::~loader()
{
}

std::filesystem::path loader::entities_path() const
{
    return _entities_path;
}

std::vector<std::shared_ptr<resource>> loader::resources() const
{
    return _resources;
}

void loader::fetch_content()
{
    auto join = [this](auto const& p) { _resources.push_back(build_resource(p)); };
    std::ranges::for_each(std::filesystem::directory_iterator(_entities_path), join);
}

std::shared_ptr<resource> loader::build_resource(std::filesystem::path const& entity_path)
{
    if (entity_path.extension() != ".md")
        return nullptr;

    std::stringstream content;
    std::ifstream entity{entity_path, std::ios::in};

    if (entity.is_open())
    {
        content << entity.get();
        entity.close();
    }
    else
    {
        return nullptr;
    }

    markdown_book_builder builder{};

    builder.read_title(content);
    builder.read_chapters(content);

    return builder.result();
}
