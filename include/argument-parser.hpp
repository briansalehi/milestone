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
#include <boost/program_options.hpp>

constexpr auto copyright {
R"(Flashback  Copyright (C) 2022  Brian Salehi (salehibrian@gmail.com)
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.)" };

namespace flashback
{
// namespace aliases
namespace options = boost::program_options;

struct argument_parser
{

    // member functions
    explicit argument_parser(int, char**, std::string const&);
    void parse_options();
    void verify_options();
    std::string get_help() const;
    std::string get_copyright() const;

    // member variables
    options::options_description all_options;
    options::options_description general_options;
    options::options_description practice_options;
    options::positional_options_description positional_options;
    options::command_line_parser command_line_parser;
    options::variables_map variables_map;
    std::string help_string;

    // option values
    bool begin_practice = false;
    std::string sample_path;
}; // options
} // flashback