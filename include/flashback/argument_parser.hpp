/*
 *  Flashback is a technical recollection program.
 *  Copyright (C) 2022  Brian Salehi (salehibrian@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>
#include <filesystem>
#include <boost/program_options.hpp>

namespace flashback
{

struct argument_parser
{
    // methods
    explicit argument_parser(int, char**, std::string const&);
    void parse_options();
    void verify_options();
    std::string get_help() const;

    // members
    boost::program_options::options_description all_options;
    boost::program_options::options_description general_options;
    boost::program_options::options_description practice_options;
    boost::program_options::positional_options_description positional_options;
    boost::program_options::command_line_parser command_line_parser;
    boost::program_options::variables_map variables_map;
    std::string help_string;

    // option values
    bool begin_practice;
    bool quiet;
    std::string program_name;
    std::string section;
    std::filesystem::path resources_path;
};
} // flashback
