#include <milestone/options.hpp>
#include <filesystem>

using namespace milestone;

options::options(int const argc, char** argv)
    : args(argv + 1, argv + argc)
{
    boost::program_options::options_description general_options{"Options"};
    general_options.add_options()
        ("help,h", "help menu")
        ("version,v", "program version");

    boost::program_options::parsed_options parsed_options{boost::program_options::command_line_parser(argc, argv).options(general_options).run()};
    boost::program_options::store(parsed_options, vmap);
    vmap.notify();

    if (vmap.contains("help"))
    {
        std::ostringstream stream{};
        std::filesystem::path program_path{argv[0]};
        stream << program_path.filename().string() << " [options]\n\n";
        stream << general_options;
        throw terminating_argument{stream.str()};
    }

    if (vmap.contains("version"))
    {
        std::filesystem::path program_path{argv[0]};
        std::string program_info{program_path.filename().string() + " version " + PROGRAM_VERSION};
        throw terminating_argument{program_info};
    }
}