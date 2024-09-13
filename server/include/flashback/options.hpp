#pragma once

#include <boost/program_options.hpp>
#include <filesystem>
#include <string>

namespace flashback
{
class options
{
public:
    options();
    void parse(int argc, char const** argv);
    friend std::ostream& operator<<(std::ostream& buffer, options const& object);
    operator std::string() const;

public:
    std::string address;
    std::uint16_t port;
    std::filesystem::path logfile;
    bool ipv4_only;
    bool ipv6_only;

private:
    boost::program_options::options_description all_options;
    boost::program_options::options_description general_options;
    boost::program_options::options_description server_options;
    boost::program_options::positional_options_description positional_options;
    boost::program_options::variables_map arguments;
};
} // flashback
