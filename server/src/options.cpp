#include <flashback/options.hpp>
#include <stdexcept>
#include <format>

namespace flashback
{
options::options() :
    all_options{},
    general_options{"General Options"},
    server_options{"Server Options"},
    positional_options{},
    arguments{},
    logfile{},
    address{},
    port{},
    ipv4_only{false},
    ipv6_only{false}
{
    general_options.add_options()
        ("help,h", "show help menu")
        ("version,v", "show program version")
        ("log,l", boost::program_options::value<std::string>(), "file path in which server log is written");

    server_options.add_options()
        ("address,a", boost::program_options::value<std::string>()->default_value("localhost"), "address to listen")
        ("port,p", boost::program_options::value<std::string>()->default_value("4433"), "port to bind")
        ("v4,4", "use only IP version 4")
        ("v6,6", "use only IP version 6");

    positional_options.add("address", 1).add("port", 2);

    all_options.add(general_options).add(server_options);
}

void options::parse(int argc, char const** argv)
{
    boost::program_options::basic_command_line_parser parser{argc, argv};
    parser.options(all_options).positional(positional_options);

    boost::program_options::basic_parsed_options parsed_options{parser.run()};
    boost::program_options::store(parsed_options, arguments);
    arguments.notify();

    if (arguments.count("help"))
    {
        throw std::invalid_argument{std::string{}};
    }

    if (arguments.count("version"))
    {
        throw std::runtime_error{std::format("v{}", PROGRAM_VERSION)};
    }

    if (arguments.count("log"))
    {
        logfile = arguments["log"].as<std::string>();
    }
    else
    {
        logfile = std::filesystem::temp_directory_path() / "flashback.log";
    }

    address = arguments["address"].as<std::string>();
    port = std::stoi(arguments["port"].as<std::string>());

    if (arguments.count("v4"))
    {
        ipv4_only = true;
    }

    if (arguments.count("v6"))
    {
        ipv6_only = true;
    }

    if (ipv4_only && ipv6_only)
    {
        throw std::invalid_argument{"v4 and v6 options cannot be both applied"};
    }
}

std::ostream& operator<<(std::ostream& buffer, options const& object)
{
    buffer << object.all_options;
    return buffer;
}
} // flashback
