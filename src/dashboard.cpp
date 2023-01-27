#include <flashback/dashboard.hpp>
#include <flashback/loader.hpp>

using namespace flashback;
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

dashboard::dashboard(): _stream{std::cerr, std::cin}
{
}

void dashboard::open()
{
    std::string space_name = prompt_space();
    std::shared_ptr<space> active_space = build_space(space_name);
    enter_space(active_space);
}

constexpr std::vector<std::string> dashboard::space_names() const
{
    return {"library", "trainer", "tutorials", "roadmap"};
}

std::string dashboard::prompt_space()
{
    _stream.clear();
    _stream.write("Enter one of the spaces to continue: ", console::color::white, false);

    std::size_t space_index{};

    auto index_space = [space_index, this](std::string_view space_name) mutable {
        _stream.write(std::to_string(++space_index) + ". "s + std::string{space_name} + "  "s, console::color::orange, false);
    };

    std::ranges::for_each(space_names(), index_space);

    std::string selection{};

    selection = _stream.read_string("\nSpace", console::color::white); // throws

    space_index = std::stoi(selection) - 1; // throws

    if (space_index >= space_names().size())
        throw std::out_of_range("out of range");

    selection = space_names().at(space_index);

    return selection;
}

std::shared_ptr<space> dashboard::build_space(std::string_view space_name)
{
    if (space_name == "library")
    {
        return std::make_shared<library>("postgres://postgres@localhost/flashback");
    }
    else if (space_name == "trainer")
    {
        return std::make_shared<trainer>();
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

void dashboard::enter_space(std::shared_ptr<space> active_space)
{
    if (active_space)
        active_space->init();
    else
        throw std::runtime_error("cannot initialize space");
}
