#include <flashback/options.hpp>
#include <flashback/server.hpp>
#include <iostream>
#include <print>

int main(int argc, char const** argv)
{
    flashback::options options{};

    try
    {
        options.parse(argc, argv);
        std::println("Listening on {}:{}, logging in {}", options.address, options.port, options.logfile.string());
    }
    catch (std::invalid_argument const& exp)
    {
        std::string message{options};
        std::println(std::cerr, "{}", message);
    }
    catch (std::exception const& exp)
    {
        std::println(std::cerr, "{}", exp.what());
    }
}
