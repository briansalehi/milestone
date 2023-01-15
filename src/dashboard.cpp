#include <flashback/dashboard.hpp>
#include <flashback/loader.hpp>

using namespace flashback;
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

dashboard::dashboard(): _active_space{}, _stream{std::cerr, std::cin}
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
        _stream.write(exp.what(), console::color::darkred);
    }
}

constexpr std::vector<std::string> dashboard::space_names() const
{
    return {"library", "trainer", "tutorials", "roadmap"};
}

std::string dashboard::prompt_space()
{
    _stream.write("Enter one of the spaces to continue: ", console::color::white, false);

    unsigned int space_index = 0;

    auto index_space = [space_index, this](std::string_view space_name) mutable {
        _stream.write(std::to_string(++space_index) + ". "s + std::string{space_name} + "  "s, console::color::orange, false);
    };

    std::ranges::for_each(space_names(), index_space);

    std::string selection = _stream.read_string("\nSpace", console::color::white);

    try
    {
        space_index = std::stoi(selection) - 1; // throws

        if (space_index < 0 || space_index >= space_names().size())
            throw std::out_of_range("out of range");

        selection = space_names().at(space_index);
    }
    catch (std::exception const& exp)
    {
        _stream.write(exp.what(), console::color::darkred);
        selection.clear();
    }

    return selection;
}

std::shared_ptr<space> dashboard::build_space(std::string_view space_name)
{
    if (space_name == "library")
    {
        std::filesystem::path base_path = _stream.read_string("Enter base path", console::color::darkred);

        _stream.write(space_name, console::color::green);

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
