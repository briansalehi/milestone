#include <flashback/dashboard.hpp>
#include <flashback/loader.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

dashboard::dashboard(std::string const& selection)
{
    if (selection.empty())
        enter_space(prompt());
    else
        enter_space(selection);
}

constexpr std::vector<std::string> dashboard::space_names() const
{
    return {"library", "trainer", "tutorials", "roadmap"};
}

std::string dashboard::prompt() const
{
    std::cerr << "Enter one of the spaces to continue:\n\n";

    unsigned int index = 0;

    auto index_space = [index, this](std::string_view const& space_name) mutable {
        std::cerr << " " << ++index << ". " << space_name << "\n";
    };

    std::ranges::for_each(space_names(), index_space);

    std::string selection;
    std::cout << "\nSpace: ";
    std::cin >> selection;

    if (std::soi(selection) < 0 || std::stoi(selection) >= spaces().size())
        throw std::out_of_range("space index out of range: "s + selection);

    return space_names().at(std::stoi(selection)-1);
}

void dashboard::enter_space(std::shared_ptr<space> selected_space)
{
}
