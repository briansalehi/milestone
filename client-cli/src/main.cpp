#include <iostream>
#include <print>
#include <boost/system.hpp>
#include <milestone/options.hpp>
#include <milestone/client.hpp>

int main(int const argc, char** argv)
{
    try
    {
        milestone::options const options{argc, argv};
        milestone::client client{options};
        client.make_request("/resources");
    }
    catch(milestone::terminating_argument const& arg)
    {
        // execution halts when some arguments are given
        std::println(std::cout, "{}", arg.what());
    }
    catch(boost::system::system_error const& exp)
    {
        std::println(std::cerr, "{}", exp.what());
    }
}