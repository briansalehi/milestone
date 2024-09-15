#pragma once

#include <flashback/section.hpp>
#include <cstdint>
#include <string>
#include <chrono>
#include <vector>

namespace flashback
{
struct resource
{
    constexpr resource() = default;
    constexpr resource(resource const& other) = default;
    constexpr resource& operator=(resource const& other) = default;
    constexpr resource(resource&& other) noexcept = default;
    constexpr resource& operator=(resource&& other) noexcept = default;

    constexpr auto operator<=>(resource const&) const noexcept = default;

    std::uint64_t id;
    std::string name;
    std::uint32_t incomplete_sections;
    std::uint32_t completed_sections;
    std::chrono::time_point<std::chrono::system_clock> last_study;
    std::vector<section> sections;
};
} // flashback
