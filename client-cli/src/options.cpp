#include <milestone/options.hpp>
#include <filesystem>
#include <print>

using namespace milestone;

options::options(int const argc, char** argv)
    : args(argv + 1, argv + argc)
{
    boost::program_options::options_description general_options{"Options"};
    general_options.add_options()
        ("help,h", "help menu")
        ("version,v", "program version");

    boost::program_options::options_description config_options{"Configurations"};
    config_options.add_options()
        ("server-address,a",
            boost::program_options::value<std::string>()->default_value("localhost"),
        "server address in ip or domain name"
        )
        ("server-port,p",
            boost::program_options::value<std::string>()->default_value("9821"),
            "server port number"
        );

    boost::program_options::options_description all_options;
    all_options.add(general_options).add(config_options);

    boost::program_options::parsed_options parsed_options{boost::program_options::command_line_parser(argc, argv).options(all_options).run()};
    boost::program_options::store(parsed_options, vmap);
    vmap.notify();

    if (vmap.contains("help"))
    {
        std::ostringstream stream{};
        std::filesystem::path program_path{argv[0]};
        stream << program_path.filename().string() << " [options]\n\n";
        stream << all_options;
        throw terminating_argument{stream.str()};
    }

    if (vmap.contains("version"))
    {
        std::filesystem::path program_path{argv[0]};
        std::string program_info{program_path.filename().string() + " version " + PROGRAM_VERSION};
        throw terminating_argument{program_info};
    }

    server_address = vmap.at("server-address").as<std::string>();
    server_port = vmap.at("server-port").as<std::string>();
}