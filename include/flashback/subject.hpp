#pragma once

#include <flashback/practice.hpp>
#include <flashback/topic.hpp>

#include <string>
#include <vector>
#include <memory>
#include <queue>

namespace flashback
{

class subject
{
public:
    subject();
    explicit subject(std::string const& title);

    std::string title() const;
    void title(std::string const&);
    void title(std::string&&);

    bool add_topic(std::shared_ptr<topic>);
    std::vector<std::shared_ptr<topic>> topics() const;

    std::queue<std::shared_ptr<practice>> queue_practices() const;

private:
    std::string _title;
    std::vector<std::shared_ptr<topic>> _topics;
};

} // flashback
