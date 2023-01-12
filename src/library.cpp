#include <flashback/library.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

library::library(std::filesystem::path const& source_path):
    _source_path{source_path},
    _resources{}
{
}

void library::init()
{
    // resources should be loaded in initialization.
    // they should be sorted either by recently usage of user
    // or by mostly used resources by users.
    // \todo user implementation is not complete yet.
    auto writer = [this](auto const& entry) {
        flashback::markdown_book_builder builder{entry.path()};
        builder.read_title();
        builder.read_chapters();
        _resources.push_back(builder.result());
    };

    if (std::filesystem::exists(_source_path) && std::filesystem::is_directory(_source_path))
    {
        std::ranges::for_each(std::filesystem::directory_iterator(_source_path), writer);
    }
}

void library::export_note(std::shared_ptr<note>)
{
}
