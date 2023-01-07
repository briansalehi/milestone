#include <flashback/menu.hpp>
#include <flashback/loader.hpp>

using namespace flashback;

menu::menu(std::string const& selection)
{
    flashback::loader loader{selection};
    loader.fetch_content();
}

std::vector<std::string> menu::sections() const
{
    return {"library", "trainer", "milestone", "tutorials"};
}

section menu::prompt(): const
{
}
