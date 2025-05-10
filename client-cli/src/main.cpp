#include <ncurses.h>
#include <vector>
#include <iostream>
#include <print>
#include <milestone/options.hpp>
#include <milestone/screen.hpp>
#include <boost/system.hpp>

int main(int argc, char** argv)
{
    try
    {
        milestone::options options{argc, argv};
    }
    catch(boost::system::system_error const& exp)
    {
        std::println(std::cerr, "{}", exp.what());
    }
}
