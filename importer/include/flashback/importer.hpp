#pragma once

#include <flashback/record.hpp>
#include <boost/program_options.hpp>
#include <pqxx/pqxx>

namespace flashback
{
class importer
{
public:
    explicit importer(int argc, char** argv);
    std::vector<record> records() const noexcept;
};
} // flashback
