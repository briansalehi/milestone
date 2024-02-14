#pragma once

#include <boost/program_options.hpp>

#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

namespace flashback
{

class help_requested : std::exception
{
public:
    help_requested(boost::program_options::options_description const& options)
    {
        std::ostringstream buffer;
        buffer << options;
        menu = buffer.str();
    }
    char const* what() const noexcept { return menu.c_str(); }
private:
    std::string menu;
};

struct unclosed_details_block : std::exception
{
    char const* what() const noexcept
    {
        return R"(unclosed <details> block reached)";
    }
};

struct missing_summary_margin : std::exception
{
    char const* what() const noexcept
    {
        return R"(missing empty line after <summary> tag)";
    }
};

struct unwrapped_content : std::exception
{
    char const* what() const noexcept
    {
        return R"(found line unwrapped)";
    }
};

struct missing_description : std::exception
{
    char const* what() const noexcept
    {
        return R"(missing description block)";
    }
};

struct missing_resource : std::exception
{
    char const* what() const noexcept
    {
        return R"(missing resource block)";
    }
};

struct missing_references : std::exception
{
    char const* what() const noexcept
    {
        return R"(missing references block)";
    }
};

struct description_separator_displacement : std::exception
{
    char const* what() const noexcept
    {
        return R"(description separator displacement)";
    }
};

struct resource_separator_displacement : std::exception
{
    char const* what() const noexcept
    {
        return R"(resource separator displacement)";
    }
};

struct reference_separator_displacement : std::exception
{
    char const* what() const noexcept
    {
        return R"(reference separator displacement)";
    }
};

struct broken_description_body : std::exception
{
    char const* what() const noexcept
    {
        return R"(broken description body)";
    }
};

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
