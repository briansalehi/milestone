#pragma once

#include <flashback/note.hpp>
#include <flashback/types.hpp>
#include <cstdint>
#include <string>
#include <chrono>

namespace flashback
{
struct section
{
    constexpr section() = default;
    constexpr section(section const&) = default;
    constexpr section& operator=(section const&) = default;
    constexpr section(section&&) noexcept = default;
    constexpr section& operator=(section&&) noexcept = default;

    constexpr auto operator<=>(section const&) const = default;

    std::uint64_t id;
    std::uint32_t number;
    publication_state state;
    std::string reference;
    std::chrono::time_point<std::chrono::system_clock> creation;
    std::chrono::time_point<std::chrono::system_clock> last_update;
    std::vector<note> notes;
};
} // flashback
