#pragma once

#include <cstdint>
#include <string>
#include <chrono>

namespace flashback
{
struct resource
{
    resource() = default;
    resource(resource const& other) = default;
    resource& operator=(resource const& other) = default;
    resource(resource&& other) noexcept = default;
    resource& operator=(resource&& other) noexcept = default;

    std::uint64_t id;
    std::string name;
    std::uint32_t incomplete_sections;
    std::uint32_t completed_sections;
};
} // flashback
