#pragma once

#include <flashback/resource.hpp>
#include <flashback/subject.hpp>
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

    std::string get_section_pattern(std::uint64_t const resource_id);

    std::vector<resource> studying_resources();

    std::vector<resource> editing_resources();

    std::vector<subject> subjects();

    std::vector<section> studying_sections(std::uint64_t const resource_id);

    std::vector<section> editing_sections(std::uint64_t const resource_id);

    std::vector<note> section_studying_notes(std::uint64_t const section_id);

    std::vector<note> section_editing_notes(std::uint64_t const section_id);

private:
    pqxx::connection m_connection;
};
} // flashback
