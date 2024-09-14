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

std::vector<resource> database::resources()
{
    constexpr auto query{R"(
        select resource_id, resource, incomplete_sections
        from flashback.get_user_resources(1)
        order by subject_id, updated asc nulls first;)"};
    pqxx::work work(m_connection);
    pqxx::result result{work.exec(query)};
    work.commit();

    std::vector<resource> resources(result.affected_rows());

    for (pqxx::row const& row: result)
    {
        resource resource{};
        resource.id = row.at(0).as<std::uint64_t>();
        resource.name = row.at(1).as<std::string>();
        resource.incomplete_sections = row.at(2).as<std::uint32_t>();

        resources.push_back(resource);
    }

    return resources;
}

} // flashback
