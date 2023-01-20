#pragma once

#include <flashback/practice.hpp>

#include <algorithm>
#include <utility>
#include <string>
#include <memory>
#include <vector>
#include <ranges>

namespace flashback
{

class topic
{
public:
    topic();
    explicit topic(std::string const&);

    std::string title() const;
    void title(std::string const&);
    void title(std::string&&);

    bool add_practice(std::shared_ptr<practice>);
    std::vector<std::shared_ptr<practice>> practices() const;

    std::vector<std::shared_ptr<practice>> candidates(std::size_t = 1);

private:
    std::string _title;
    std::vector<std::shared_ptr<practice>> _practices;
};

} // flashback
