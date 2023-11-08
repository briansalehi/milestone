#include <flashback/dashboard.hpp>

using namespace flashback;

void dashboard::dashboard(argument_parser const& options)
{
    std::ranges::transform(
            std::filesystem::directory_iterator(options.resource_directory),
            std::back_inserter(_topics),
            parse_topic);
}

/*
void dashboard::open()
{
    char space_id = prompt_space();
    std::shared_ptr<space> selected_space = build_space(space_id);
    enter_space(selected_space);
}

char dashboard::prompt_space()
{
    std::map<char, std::string> spaces {
        {'i', "library space"s},
      //{'u', "tutorials space"s},
      //{'r', "roadmap space"s},
        {'t', "training space"s},
        {'q', "quit from flashback"s}
    };

    char selected_space;

    _stream.clear();
    _stream << style::bold << color::blue;
    _stream.header("Flashback");
    _stream << style::bold << color::white << "\n";
    _stream << "Enter one of the spaces to continue:\n\n";
    _stream << color::pink;

    //std::ranges::for_each(spaces, std::ostream_iterator<char>(std::cout, "\n"));
    std::ranges::for_each(spaces, [](auto const& option) {
        std::cout << "  [" << option.first << "] " << option.second << "\n";
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
        case 't': selected_space = std::make_shared<training>(); break;
        case 'u': selected_space = nullptr; break;
        case 'r': selected_space = nullptr; break;
        case 'q': selected_space = nullptr; break;
        default: throw std::invalid_argument("incorrect space");
    }

    return selected_space;
}

void dashboard::enter_space(std::shared_ptr<space> selected_space)
{
    if (selected_space)
        selected_space->init();
}
*/
