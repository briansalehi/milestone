#include <flashback/dashboard.hpp>
#include <flashback/loader.hpp>

using namespace flashback;
using namespace std::literals::string_literals;

dashboard::dashboard(): _active_space{}
{
}

void dashboard::open()
{
    try
    {
        _active_space.reset();
        _active_space = build_space(prompt_space());
        enter_space();
    }
    catch (std::exception const& exp)
    {
        std::cerr << "\e[1;31m" << exp.what() << "\e[0m\n";
    }
}

constexpr std::vector<std::string> dashboard::space_names() const
{
    return {"library", "trainer", "tutorials", "roadmap"};
}

std::string dashboard::prompt_space() const
{
    std::cerr << "\e[1;37mEnter one of the spaces to continue:\n\n\e[1;33m";

    unsigned int space_index = 0;

    auto index_space = [space_index, this](std::string_view space_name) mutable {
        std::cerr << " " << ++space_index << ". " << space_name << "   ";
    };

    std::ranges::for_each(space_names(), index_space);

    std::string selection;

    std::cerr << "\n\n\e[1;37mSpace: ";
    std::cin >> selection;
    std::cerr << "\e[0m";

    try
    {
        space_index = std::stoi(selection) - 1; // throws

        if (space_index < 0 || space_index >= space_names().size())
            throw std::out_of_range("out of range");

        selection = space_names().at(space_index);
    }
    catch (std::exception const& exp)
    {
        std::cerr << "\e[1;31m" << exp.what() << "\e[0m\n";
        selection.clear();
    }

    return selection;
}

std::shared_ptr<space> dashboard::build_space(std::string_view space_name)
{
    if (space_name == "library")
    {
        std::filesystem::path base_path;
        std::cerr << "\e[1;27mEnter base path: ";
        std::cin >> base_path;
        std::cerr << "\e[0m\n";

        std::cerr << "\e[1;32mSpace " << space_name << "\e[0m\n\n";

        return std::make_shared<library>(base_path);
    }
    else if (space_name == "trainer")
    {
        return nullptr;
    }
    else if (space_name == "tutorials")
    {
        return nullptr;
    }
    else if (space_name == "milestone")
    {
        return nullptr;
    }
    else
    {
        return nullptr;
    }
}

void dashboard::enter_space()
{
    if (_active_space)
        _active_space->init();
    else
        throw std::runtime_error("cannot initialize space");
}
