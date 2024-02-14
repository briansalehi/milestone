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

    // consider the first positional argument as the resource path
    positional.add("resource", 1);

    try
    {
        // no arguments means the user has no idea how to use the program
        if (argc == 1)
            throw help_requested{user_options};

        // this block might throw when arguments don't match as specified
        boost::program_options::command_line_parser parser{argc, argv};
        parser = parser.options(user_options).positional(positional);
        boost::program_options::store(parser.run(), option_mapper);
        boost::program_options::notify(option_mapper);

        // when user requsted for help rewind stack and show help menu in caller
        if (option_mapper.contains("help"))
            throw help_requested{user_options};

        // populate option values
        resource_path = option_mapper["resource"].as<std::string>();
        debug_flag    = option_mapper.contains("debug");
        brief_flag    = option_mapper.contains("brief");
        quiet_flag    = option_mapper.contains("quiet");
        error_flag    = option_mapper.contains("error");
        complete_flag = option_mapper.contains("complete");
        writing_flag  = option_mapper.contains("writing");

        // conflicts and missing prerequisites that cannot be handled here
        if (debug_flag && (quiet_flag || brief_flag))
            throw std::invalid_argument{"debugging cannot be done silently"};
        else if (quiet_flag && (complete_flag || writing_flag))
            throw std::invalid_argument{"cannot log details in quiet mode"};
        else if (resource_path.empty())
            throw std::invalid_argument{"resource path not given"};
        else if (!std::filesystem::exists(resource_path))
            throw std::invalid_argument{"resource path does not exist"};
        else if (
                !std::filesystem::is_regular_file(resource_path) &&
                !std::filesystem::is_directory(resource_path)
            )
            throw std::invalid_argument{
                "resource should be a regular file or directory"};

        // conflicts and prerequisites that can possibly be handled here
        if (quiet_flag && brief_flag)
            brief_flag = false;
    }
    catch (boost::program_options::required_option const& exp)
    {
        throw help_requested{user_options};
    }
}

} // flashback

int main(int argc, char** argv)
{
    try
    {
        flashback::argument_parser options{argc, argv};

    }
    catch (flashback::help_requested const& exp)
    {
        std::cerr << exp.what() << std::endl;
    }
    catch (std::exception const& exp)
    {
        std::cerr << exp.what() << std::endl;
    }
}
