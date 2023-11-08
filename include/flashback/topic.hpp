#pragma once

#include <flashback/practice.hpp>

#include <string>
#include <memory>
#include <vector>
#include <compare>

namespace flashback
{

class topic: public std::enable_shared_from_this<topic>
{
public:
    topic(std::string);

    topic(topic const&);
    topic(topic&&) noexcept;
    topic& operator=(topic const&);
    topic& operator=(topic&&) noexcept;

    std::string title() const;

    void add_practice(practice const&);
    void add_practice(practice&&) noexcept;
    std::vector<practice> practices() const;

    auto operator<=>(topic const&) = default;

private:
    std::string _title;
    std::vector<practice> _practices;
};

} // flashback
