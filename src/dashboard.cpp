#include <flashback/dashboard.hpp>
#include <flashback/loader.hpp>

using namespace flashback;
using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

dashboard::dashboard(): _stream{std::cin, std::cout}
{
}

void dashboard::open()
{
    char space_id = prompt_space();
    std::shared_ptr<space> selected_space = build_space(space_id);
    enter_space(selected_space);
}

constexpr std::vector<std::string> dashboard::space_names() const
{
    return {"library", "trainer", "tutorials", "roadmap"};
}

char dashboard::prompt_space()
{
    std::vector<std::string> spaces {
        "[i] library",
        "[t] trainer",
        "[u] tutorials",
        "[r] roadmap"
    };

    char selected_space;

    _stream.clear();
    _stream << style::bold << color::blue;
    _stream.header("Flashback");
    _stream << style::bold << color::white << "\n";
    _stream << "Enter one of the spaces to continue:\n\n";
    _stream << color::pink;

    //std::ranges::for_each(spaces, std::ostream_iterator<char>(std::cout, "\n"));
    std::ranges::for_each(spaces, [](std::string const& s) {
        std::cout << "  " << s << "\n";
    });

    _stream << color::white;
    _stream << "\nSpace: ";

    std::cin >> selected_space;
    _stream << color::reset;

    return selected_space;
}

std::shared_ptr<space> dashboard::build_space(char space_id)
{
    std::shared_ptr<space> selected_space{};

    switch (space_id)
    {
        case 'i': selected_space = std::make_shared<library>(); break;
        case 't': selected_space = std::make_shared<trainer>(); break;
        case 'u': selected_space = nullptr; break;
        case 'r': selected_space = nullptr; break;
        default: throw std::invalid_argument("incorrect space");
    }

    return selected_space;
}

void dashboard::enter_space(std::shared_ptr<space> selected_space)
{
    if (selected_space)
        selected_space->init();
    else
        throw std::runtime_error("cannot initialize space");
}
