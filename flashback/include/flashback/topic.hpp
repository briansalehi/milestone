#pragma once

#include <cstdint>
#include <string>
#include <chrono>

namespace flashback
{
struct topic
{
    constexpr topic() = default;
    constexpr topic(topic const&) = default;
    constexpr topic& operator=(topic const&) = default;
    constexpr topic(topic&&) noexcept = default;
    constexpr topic& operator=(topic&&) noexcept = default;

    constexpr auto operator<=>(topic const&) const noexcept = default;

    std::uint64_t id;
    std::string name;
    std::uint32_t position;
    std::chrono::time_point<std::chrono::system_clock> creation;
    std::chrono::time_point<std::chrono::system_clock> last_update;
};
} // flashback
