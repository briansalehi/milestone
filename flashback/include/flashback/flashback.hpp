#pragma once

#include <flashback/resource.hpp>
#include <flashback/subject.hpp>
#include <pqxx/pqxx>
#include <string>

namespace flashback
{
class database
{
public:
    database();
    explicit database(std::string const& address);

    bool is_connected() const noexcept;

    std::string address() const;

    std::vector<resource> studying_resources();

    std::vector<resource> editing_resources();

    std::vector<subject> subjects();

private:
    pqxx::connection m_connection;
};
} // flashback
