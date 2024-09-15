#pragma once

#include <flashback/topic.hpp>
#include <flashback/resource.hpp>
#include <cstdint>
#include <string>
#include <chrono>
#include <vector>

namespace flashback
{
struct subject
{
    constexpr subject() = default;
    constexpr subject(subject const&) = default;
    constexpr subject(subject&&) noexcept = default;
    constexpr subject& operator=(subject const&) = default;
    constexpr subject& operator=(subject&&) noexcept = default;

    constexpr auto operator<=>(subject const&) const noexcept = default;

    std::uint64_t id;
    std::string name;
    std::chrono::time_point<std::chrono::system_clock> last_update;
    std::vector<topic> topics;
    std::vector<resource> resources;
};
} // flahback
