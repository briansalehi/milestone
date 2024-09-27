#pragma once

#include <flashback/block.hpp>
#include <string>
#include <cstdint>
#include <chrono>
#include <vector>

namespace flashback
{
struct practice
{
    constexpr practice() = default;
    constexpr practice(practice const&) = default;
    constexpr practice(practice&&) noexcept = default;
    constexpr practice& operator=(practice const&) = default;
    constexpr practice& operator=(practice&&) noexcept = default;

    constexpr auto operator<=>(practice const&) const = default;

    std::uint64_t id;
    std::string heading;
    std::uint32_t position;
    std::chrono::time_point<std::chrono::system_clock> creation;
    std::chrono::time_point<std::chrono::system_clock> last_update;
    std::vector<block> blocks;
};
} // flashback
