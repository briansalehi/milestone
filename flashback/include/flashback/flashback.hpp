#pragma once

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

private:
    pqxx::connection m_connection;
};
} // flashback
