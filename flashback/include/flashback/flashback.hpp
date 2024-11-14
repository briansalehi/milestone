#pragma once

#include <flashback/subject.hpp>
#include <flashback/topic.hpp>
#include <flashback/practice.hpp>
#include <flashback/resource.hpp>
#include <flashback/section.hpp>
#include <flashback/note.hpp>
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

    std::string section_pattern(std::uint64_t const resource_id);
    std::vector<subject> subjects();
    std::vector<topic> topics(std::uint64_t subject_id);
    std::vector<practice> practices(std::uint64_t topic_id);
    std::vector<block> practice_blocks(std::uint64_t practice_id);
    std::vector<resource> resources();
    std::vector<section> sections(std::uint64_t const resource_id);
    std::vector<note> notes(std::uint64_t const section_id);
    std::vector<block> note_blocks(std::uint64_t const note_id);

    void section_study_completed(std::uint64_t const section_id);

private:
    pqxx::connection m_connection;
};
} // flashback
