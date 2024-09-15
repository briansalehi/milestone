#pragma once

#include <flashback/types.hpp>
#include <cstdint>
#include <string>
#include <chrono>
#include <vector>

namespace flashback
{
struct note_block
{
    constexpr note_block() = default;
    constexpr note_block(note_block const&) = default;
    constexpr note_block(note_block&&) noexcept = default;
    constexpr note_block& operator=(note_block const&) = default;
    constexpr note_block& operator=(note_block&&) noexcept = default;

    constexpr auto operator<=>(note_block const&) const noexcept = default;

    std::uint64_t id;
    std::uint32_t position;
    std::string content;
    block_type type;
    char language[10];
    std::chrono::time_point<std::chrono::system_clock> last_update;
    std::vector<std::string> references;
};
} // flashback
