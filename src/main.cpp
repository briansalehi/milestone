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

#include <thread>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <algorithm>
#include <filesystem>

#include <boost/program_options.hpp>
#include <flashback/dashboard.hpp>

void launch_practice()
{
    try
    {
        flashback::dashboard dashboard{};
        dashboard.open();
    }
    catch (std::exception const& exp)
    {
        std::cerr << exp.what() << '\n';
    }
}

int main(int argc, char **argv)
{
    try
    {
        std::string program_name{std::filesystem::path{argv[0]}.filename()};
        flashback::argument_parser options(argc, argv, program_name);

        std::jthread user_session(launch_practice);
    }
    catch (boost::program_options::error const& exp)
    {
        std::cerr << exp.what() << '\n';
        return 1;
    }
    catch (std::exception const& exp)
    {
        std::cerr << "\e[1;31m" << exp.what() << "\e[0m\n";
        return 2;
    }
}
