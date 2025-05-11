#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <milestone/exceptions.hpp>

namespace milestone
{
class options
{
public:
    explicit options(int argc, char** argv);
public:
    std::string server_address;
    std::string server_port;
private:
    std::vector<std::string> args;
    boost::program_options::variables_map vmap;
};
} // milestone