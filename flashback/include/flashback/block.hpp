#pragma once

#include <flashback/types.hpp>
#include <cstdint>
#include <string>
#include <chrono>
#include <vector>

namespace flashback
{
struct block
{
    constexpr block() = default;
    constexpr block(block const&) = default;
    constexpr block(block&&) noexcept = default;
    constexpr block& operator=(block const&) = default;
    constexpr block& operator=(block&&) noexcept = default;

    constexpr auto operator<=>(block const&) const noexcept = default;

    std::uint64_t id;
    std::uint32_t position;
    std::string content;
    block_type type;
    std::string language;
    std::chrono::time_point<std::chrono::system_clock> last_update;
    std::vector<std::string> references;
};
} // flashback
