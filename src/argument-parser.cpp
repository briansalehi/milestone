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
#include <argument-parser.hpp>

using namespace flashback;

argument_parser::argument_parser(int argc, char **argv)
    : command_line_parser(argc, argv),
    general_options("Options"),
    practice_options("Practice Options")
{
    general_options.add_options()
        ("help,h", "show help message");

    practice_options.add_options()
        ("reset,r", "start over all practices");

    all_options.add(general_options).add(practice_options);

    command_line_parser.options(all_options).positional(positional_options);

    parse_options();
    verify_options();
}

void argument_parser::parse_options()
{
    // throws options::error
    auto parsed_options = command_line_parser.run();
    options::store(parsed_options, variables_map);
    options::notify(variables_map);
}

void argument_parser::verify_options()
{
    if (variables_map.count("help"))
    {
        std::ostringstream buffer;
        buffer << all_options;
        throw options::error(buffer.str());
    }

    begin_practice = true;
}
