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

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <filesystem>

#include <argument-parser.hpp>
#include <session.hpp>

int main(int argc, char **argv)
{
    try
    {
        using namespace std::literals::string_literals;

        std::string program_name{std::filesystem::path(argv[0]).filename()};
        flashback::argument_parser options(argc, argv, program_name);

        if (options.begin_practice && !options.sample_path.empty())
        {
            std::ifstream sample(options.sample_path);

            if (std::stringstream buffer; sample.is_open())
            {
                std::string line;
                while (getline(sample, line))
                {
                    buffer << line << "\n";
                }

                flashback::card sample_card(buffer);
                sample.close();
            }
        }
        else
        {
            std::cerr << options.get_help();
        }

        return 0;
    }
    catch (boost::program_options::error const& exp)
    {
        std::cerr << exp.what() << std::endl;
    }
    catch (std::exception const& exp)
    {
        std::cerr << exp.what() << std::endl;
    }

    return 1;
}
