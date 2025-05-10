#pragma once

#include <vector>
#include <string>
#include <boost/program_options.hpp>
#include <milestone/exceptions.hpp>

namespace milestone
{
class options
{
public:
    explicit options(int const argc, char** argv);

private:
    std::vector<std::string> args;
    boost::program_options::variables_map vmap;
};
} // milestone
