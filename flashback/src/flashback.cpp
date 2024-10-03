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

std::string database::section_pattern(std::uint64_t const resource_id)
{
    std::string pattern{};

    try
    {
        pqxx::work work(m_connection);
        std::string query{std::format(R"(select pattern from get_section_pattern({});)", resource_id)};
        pattern = work.exec1(query).at("pattern").as<std::string>();
    }
    catch (...)
    {
    }

    return pattern;
}

std::vector<resource> database::resources()
{
    constexpr auto query{R"(
        select *
        from get_user_studying_resources(1)
        order by last_study desc nulls last, incomplete_sections desc, completed_sections desc, total_sections desc;
    )"};
    pqxx::work work(m_connection);
    pqxx::result result{work.exec(query)};
    work.commit();

    std::vector<resource> resources;
    resources.reserve(result.affected_rows());

    for (pqxx::row const& row: result)
    {
        resource resource{};
        resource.id = row.at("resource_id").as<std::uint64_t>();
        resource.name = row.at("resource").as<std::string>();
        resource.completed_sections = row.at("completed_sections").as<std::uint64_t>();
        resource.incomplete_sections = row.at("incomplete_sections").as<std::uint64_t>();

        resource.sections.resize(row.at("total_sections").as<std::uint64_t>());

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

    std::vector<subject> subjects;
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

std::vector<topic> database::topics(std::uint64_t subject_id)
{
    constexpr std::uint64_t user_id{1};

    std::string query{std::format(R"(
        select subject_id, topic_id, topic_position, name, practices, updated
        from flashback.get_user_topics({}, {})
        order by updated asc nulls first, topic_position asc, practices desc, topic_id asc;
    )", user_id, subject_id)};

    pqxx::work work{m_connection};
    pqxx::result result{work.exec(query)};
    work.commit();

    std::vector<topic> topics;
    topics.reserve(result.affected_rows());

    for (pqxx::row const& row: result)
    {
        topic topic{};
        topic.id = row.at("topic_id").as<std::uint64_t>();
        topic.name = row.at("name").as<std::string>();
        topic.position = row.at("topic_position").as<std::uint32_t>();
        topic.practices.clear();
        topic.practices.resize(row.at("practices").as<std::uint64_t>());

        topics.push_back(topic);
    }

    return topics;
}

std::vector<practice> database::practices(std::uint64_t topic_id)
{
    constexpr std::uint64_t user_id{1};

    std::string query{std::format(R"(
        select id, heading, pos, content, updated
        from flashback.get_user_practices({}, {})
        order by updated asc nulls first, pos asc, heading asc;
    )", user_id, topic_id)};

    pqxx::work work{m_connection};
    pqxx::result result{work.exec(query)};
    work.commit();

    std::vector<practice> practices;
    practices.reserve(result.affected_rows());

    for (pqxx::row const& row: result)
    {
        practice practice{};
        practice.id = row.at("id").as<std::uint64_t>();
        practice.heading = row.at("heading").as<std::string>();
        practice.position = row.at("pos").as<std::uint32_t>();
        std::stringstream blocks(row.at("content").as<std::string>());
        block block{};
        block.content = blocks.str();
        practice.blocks.push_back(block);

        practices.push_back(practice);
    }

    return practices;
}

std::vector<section> database::sections(uint64_t const resource_id)
{
    std::string query{std::format(R"(select * from get_sections({}) order by section_number;)", resource_id)};
    pqxx::work work(m_connection);
    pqxx::result result{work.exec(query)};
    work.commit();

    std::vector<section> sections;
    sections.reserve(result.affected_rows());

    for (pqxx::row const& row: result)
    {
        section section{};
        section.id = row.at("section_id").as<std::uint64_t>();
        section.number = row.at("section_number").as<std::uint32_t>();
        std::string state{row.at("section_state").as<std::string>()};
        if (state == "open") section.state = publication_state::open;
        else if (state == "writing") section.state = publication_state::writing;
        else if (state == "completed") section.state = publication_state::completed;
        else if (state == "revised") section.state = publication_state::revised;
        else if (state == "validated") section.state = publication_state::validated;
        else if (state == "approved") section.state = publication_state::approved;
        else if (state == "released") section.state = publication_state::released;
        else if (state == "ignored") section.state = publication_state::ignored;
        sections.push_back(section);
    }

    return sections;
}

std::vector<note> database::notes(const uint64_t section_id)
{
    std::string query{std::format(R"(select * from get_section_study_notes({}) order by creation asc;)", section_id)};
    pqxx::work work(m_connection);
    pqxx::result result{work.exec(query)};
    work.commit();

    std::vector<note> notes;
    notes.reserve(result.affected_rows());

    for (pqxx::row const& row: result)
    {
        note note{};
        note.id = row.at("note_id").as<std::uint64_t>();

        std::string state{row.at("note_state").as<std::string>()};
        if (state == "open") note.state = publication_state::open;
        else if (state == "writing") note.state = publication_state::writing;
        else if (state == "completed") note.state = publication_state::completed;
        else if (state == "revised") note.state = publication_state::revised;
        else if (state == "validated") note.state = publication_state::validated;
        else if (state == "approved") note.state = publication_state::approved;
        else if (state == "released") note.state = publication_state::released;
        else if (state == "ignored") note.state = publication_state::ignored;

        note.heading = row.at("heading").as<std::string>();
        block block{};
        block.content = row.at("content").as<std::string>();
        note.blocks.push_back(block);

        std::tm datetime{};
        std::istringstream creation_stream{row.at("creation").as<std::string>()};
        creation_stream >> std::get_time(&datetime, "%Y-%m-%d %H:%M:%S");
        note.creation = std::chrono::system_clock::from_time_t(std::mktime(&datetime));

        std::istringstream last_update_stream{row.at("last_update").as<std::string>()};
        last_update_stream >> std::get_time(&datetime, "%Y-%m-%d %H:%M:%S");
        note.last_update = std::chrono::system_clock::from_time_t(std::mktime(&datetime));

        notes.push_back(note);
    }

    return notes;
}

} // flashback
