#pragma once

#include <flashback/types.hpp>
#include <flashback/note_block.hpp>
#include <string>
#include <cstdint>
#include <chrono>
#include <vector>

namespace flashback
{
struct note
{
    constexpr note() = default;
    constexpr note(note const&) = default;
    constexpr note& operator=(note const&) = default;
    constexpr note(note&&) noexcept = default;
    constexpr note& operator=(note&&) noexcept = default;

    constexpr auto operator<=>(note const&) const noexcept = default;

    std::uint64_t id;
    std::string heading;
    publication_state state;
    std::chrono::time_point<std::chrono::system_clock> creation;
    std::chrono::time_point<std::chrono::system_clock> last_update;
    std::vector<note_block> blocks;
};
} // flashback
