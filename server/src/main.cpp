#include <iostream>
#include <flashback/options.hpp>
//#include <flashback/server.hpp>

int main(int argc, char const** argv)
{
    flashback::options options{};

    try
    {
        options.parse(argc, argv);
        std::cout << options.address << std::endl;
        std::cout << options.port << std::endl;
        std::cout << options.logfile << std::endl;
    }
    catch (std::invalid_argument const& exp)
    {
        std::cerr << options << std::endl;
    }
    catch (std::exception const& exp)
    {
        std::cerr << exp.what() << std::endl;
    }
}
