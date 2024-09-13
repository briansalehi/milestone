#include <boost/program_options.hpp>
#include <pqxx/pqxx>
#include <filesystem>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ios>

int main(int argc, char** argv)
{
    try
    {
        boost::program_options::options_description description{"Options"};
        boost::program_options::positional_options_description positional{};
        description.add_options()("help,h", "show help menu")("base,b", boost::program_options::value<std::string>(), "records directory path");
        positional.add("base", -1);
        boost::program_options::variables_map options{};
        boost::program_options::basic_command_line_parser<char> parser = boost::program_options::command_line_parser(argc, argv);
        boost::program_options::basic_parsed_options<char> parsed = parser.options(description).positional(positional).run();
        boost::program_options::store(parsed, options);
        boost::program_options::notify(options);

        if (argc == 1 || options.count("help") > 0)
        {
            std::cerr << std::filesystem::path{argv[0]}.filename().string() << " <path/to/records>\n\n";
            std::cerr << description << std::endl;
            return 1;
        }

        if (options.count("base") == 0)
        {
            throw std::invalid_argument{"records directory path should be specified."};
        }

        std::filesystem::path records_path{options["base"].as<std::string>()};

        pqxx::connection connection{"postgres://localhost/flashback"};
        pqxx::work task{connection};
        std::size_t imported{};

        for (auto const& entry: std::filesystem::directory_iterator{records_path})
        {
            if (entry.path().extension().string() == ".sql")
            {
                std::filesystem::path record_path = entry.path().lexically_normal();
                std::ifstream file{record_path};
                std::streamoff size{file.tellg()};
                std::string buffer(size, '\0');
                file.seekg(0);
                file.read(buffer.data(), size);
                task.exec(std::move(buffer));
                imported++;
            }
        }

        std::cerr << imported << " records added.\n";
    }
    catch (std::exception const& exp)
    {
        std::cerr << exp.what() << std::endl;
    }
}
