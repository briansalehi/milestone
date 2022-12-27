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

#include <sstream>
#include <iostream>
#include <argument-parser.hpp>

using namespace flashback;

argument_parser::argument_parser(int argc, char **argv, std::string const& program_name)
    : program_name{program_name},
    command_line_parser(argc, argv),
    general_options("Options"),
    practice_options("Practice Options")
{
    general_options.add_options()
        ("help,h", "show help message");

    practice_options.add_options()
        ("file,f", boost::program_options::value<std::string>(), "input file")
        ("reset,r", "start over all practices");

    all_options.add(general_options).add(practice_options);

    command_line_parser.options(all_options).positional(positional_options);

    parse_options();
    verify_options();
}

void argument_parser::parse_options()
{
    // throws boost::program_options::error
    auto parsed_options = command_line_parser.run();
    boost::program_options::store(parsed_options, variables_map);
    boost::program_options::notify(variables_map);
}

void argument_parser::verify_options()
{
    if (variables_map.count("help"))
    {
        throw std::invalid_argument(get_help());
    }

    if (variables_map.count("file"))
    {
        sample_path = variables_map["file"].as<std::string>();
    }

    begin_practice = true;
}

std::string argument_parser::get_help() const
{
    std::ostringstream buffer;
    buffer << "Usage: " << program_name << " [options]\n";
    buffer << all_options;
    return buffer.str();
}
