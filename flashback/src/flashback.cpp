#include <flashback/flashback.hpp>

namespace flashback
{

database::database()
{
}

database::database(std::string const& address)
    : m_connection{address}
{
}

bool database::is_connected() const noexcept
{
    return m_connection.is_open();
}

std::string database::address() const
{
    return m_connection.connection_string();
}

} // flashback
