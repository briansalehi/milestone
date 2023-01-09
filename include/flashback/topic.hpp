#pragma once

#include <flashback/practice.hpp>

#include <utility>
#include <string>
#include <memory>
#include <vector>
#include <set>

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
    std::set<std::shared_ptr<practice>> practices() const;

private:
    std::string _title;
    std::set<std::shared_ptr<practice>> _practices;
};

} // flashback
