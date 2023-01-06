#include <flashback/menu.hpp>

using namespace flashback;

menu::menu(std::string const& section)
{
    flashback::loader loader{options.resources_path};
    loader.fetch_content();
}

std::vector<std::string> menu::sections() const
{
    return {"library", "trainer", "milestone", "tutorials"};
}
