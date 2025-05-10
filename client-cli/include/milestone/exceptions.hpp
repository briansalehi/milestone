#pragma once

#include <string>
#include <exception>

namespace milestone
{
class terminating_argument final : public std::exception
{
public:
    explicit terminating_argument(std::string reason): description{std::move(reason)}
    {
    }

    [[nodiscard]] char const* what() const noexcept override
    {
        return description.c_str();
    }

private:
    std::string description;
};
} // milestone