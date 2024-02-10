#pragma once

#include <boost/program_options.hpp>

#include <filesystem>
#include <iostream>
#include <string>
#include <thread>

namespace flashback
{

class argument_parser
{
public:
    argument_parser(int argc, char** argv);
public:
    boost::program_options::options_description user_options;
    std::filesystem::path resource_path;
private:
    boost::program_options::positional_options_description positional;
    boost::program_options::variables_map option_mapper;
    bool brief_flag;
    bool help_flag;
    bool quiet_flag;
    bool error_flag;
    bool debug_flag;
    bool complete_flag;
    bool writing_flag;
};

class validator
{
public:
private:
};

} // flashback
