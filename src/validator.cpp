#include <flashback/validator.hpp>

namespace flashback
{

argument_parser::argument_parser(int argc, char** argv)
    : user_options{"Options"}
{
    user_options.add_options()
        ("resource,r",  boost::program_options::value<std::string>()->required(),
                        "path to the source directory or file")
        ("help,h",      "show this help menu")
        ("debug,d",     "enable debug output")
        ("brief,b",     "logs output as few as possible")
        ("quiet,q",     "disable output, suitable for scripts")
        ("error,e",     "treat warnings as errors")
        ("complete,c",  "list unpublished practices")
        ("writing,w",   "list incomplete practices");

    positional.add("resource", 1);

    try
    {
        boost::program_options::command_line_parser parser{argc, argv};
        parser = parser.options(user_options).positional(positional);
        boost::program_options::store(parser.run(), option_mapper);
        boost::program_options::notify(option_mapper);

        if (option_mapper.contains("help"))
            std::cout << user_options << '\n';
        else
            resource_path = option_mapper["resource"].as<std::string>();

        debug_flag    = option_mapper.contains("debug");
        brief_flag    = option_mapper.contains("brief");
        quiet_flag    = option_mapper.contains("quiet");
        error_flag    = option_mapper.contains("error");
        complete_flag = option_mapper.contains("complete");
        writing_flag  = option_mapper.contains("writing");
    }
    catch (boost::program_options::required_option const& exp)
    {
        std::cout << user_options << '\n';
    }
}

} // flashback

int main(int argc, char** argv)
{
    try
    {
        flashback::argument_parser options{argc, argv};
        std::cout << options.resource_path << std::endl;
    }
    catch (std::exception const& exp)
    {
        std::cerr << exp.what() << std::endl;
    }
}
