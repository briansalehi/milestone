#include <milestone/options.hpp>

using namespace milestone;

options::options(int argc, char** argv)
    : args(argv + 1, argv + argc)
{
    boost::program_options::options_description general_options{"Options"};
    general_options.add_options()
        ("help,h", "help menu")
        ("version,v", "program version");

//    boost::program_options::command_line_parser parsed_options(general_options, vmap).run();

    if (vmap.contains("help"))
    {
    }

    if (vmap.contains("version"))
    {
    }
}