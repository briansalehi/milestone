#include <flashback/flashback.hpp>
#include <sstream>
#include <iomanip>
#include <ctime>

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

std::vector<resource> database::editing_resources()
{
    constexpr auto query{R"(
        select *
        from get_user_editing_resources(1)
        order by subject_id, last_study asc nulls first, incomplete_sections desc, resource_id;
    )"};
    pqxx::work work(m_connection);
    pqxx::result result{work.exec(query)};
    work.commit();

    std::vector<resource> resources{};
    resources.reserve(result.affected_rows());

    for (pqxx::row const& row: result)
    {
        resource resource{};
        resource.id = row.at("resource_id").as<std::uint64_t>();
        resource.name = row.at("resource").as<std::string>();
        resource.incomplete_sections = row.at("incomplete_sections").as<std::uint32_t>();

        std::tm datetime{};
        std::istringstream datetime_stream{row.at("last_study").as<std::string>()};
        datetime_stream >> std::get_time(&datetime, "%Y-%m-%d %H:%M:%S");
        resource.last_study = std::chrono::system_clock::from_time_t(std::mktime(&datetime));

        resources.push_back(resource);
    }

    return resources;
}

std::vector<resource> database::studying_resources()
{
    constexpr auto query{R"(
        select *
        from get_user_studying_resources(1)
        order by subject_id, last_study asc nulls first, completed_sections desc, resource_id;
    )"};
    pqxx::work work(m_connection);
    pqxx::result result{work.exec(query)};
    work.commit();

    std::vector<resource> resources{};
    resources.reserve(result.affected_rows());

    for (pqxx::row const& row: result)
    {
        resource resource{};
        resource.id = row.at("resource_id").as<std::uint64_t>();
        resource.name = row.at("resource").as<std::string>();
        resource.incomplete_sections = row.at("completed_sections").as<std::uint32_t>();

        std::tm datetime{};
        std::istringstream datetime_stream{row.at("last_study").as<std::string>()};
        datetime_stream >> std::get_time(&datetime, "%Y-%m-%d %H:%M:%S");
        resource.last_study = std::chrono::system_clock::from_time_t(std::mktime(&datetime));

        resources.push_back(resource);
    }

    return resources;
}

std::vector<subject> database::subjects()
{
    constexpr auto query{R"(
        select id, name, topics, resources, updated
        from flashback.get_user_subjects(1)
        order by updated asc nulls first, topics desc, name asc;
    )"};

    pqxx::work work{m_connection};
    pqxx::result result{work.exec(query)};
    work.commit();

    std::vector<subject> subjects{};
    subjects.reserve(result.affected_rows());

    for (pqxx::row const& row: result)
    {
        subject subject{};
        subject.id = row.at("id").as<std::uint64_t>();
        subject.name = row.at("name").as<std::string>();
        subject.topics = std::vector<topic>(row.at("topics").as<std::uint32_t>());
        subject.resources = std::vector<resource>(row.at("resources").as<std::uint32_t>());

        std::tm datetime{};
        std::istringstream datetime_stream{row.at(4).as<std::string>()};
        datetime_stream >> std::get_time(&datetime, "%Y-%m-%d %H:%M:%S");
        subject.last_update = std::chrono::system_clock::from_time_t(std::mktime(&datetime));

        subjects.push_back(subject);
    }

    return subjects;
}

} // flashback
