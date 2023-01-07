#include <flashback/dashboard.hpp>
#include <flashback/loader.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

dashboard::dashboard(std::string const& selection)
{
    flashback::loader loader{selection};
    //loader.fetch_content();

    if (selection.empty())
        enter_space(prompt());
    else
        enter_space(get_space(selection));
}

constexpr std::vector<std::string> dashboard::spaces() const
{
    return {"library", "trainer", "tutorials", "roadmap"};
}

space dashboard::prompt() const
{
    std::cerr << "Enter one of the spaces to continue:\n\n";

    unsigned int index = 0;
    auto index_space = [index, this](std::string_view const& space_name) mutable {
        std::cerr << " " << ++index << ". " << space_name << "\n";
    };
    std::ranges::for_each(spaces(), index_space);

    std::string selection;
    std::cout << "\nSpace: ";
    std::cin >> selection;

    if (std::stoi(selection) < spaces().size())
        selection = spaces().at(std::stoi(selection)-1);
    else
        throw std::runtime_error("invalid space name: "s + selection);

    return get_space(selection);
}

space dashboard::get_space(std::string const& selection) const
{
    space selected_space;

    if (selection == "library")
        selected_space = space::library;
    else if (selection == "trainer")
        selected_space = space::trainer;
    else if (selection == "tutorials")
        selected_space = space::tutorials;
    else if (selection == "roadmap")
        selected_space = space::roadmap;

    return selected_space;
}

void dashboard::enter_space(space const selected_space)
{
}
