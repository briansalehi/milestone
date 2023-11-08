#include <flashback/topic.hpp>

using namespace flashback;

topic::topic(std::string title):
    _title{title},
    _practices{}
{
}

topic::topic(topic const& other):
    _title{other._title},
    _practices{other._practices}
{
}

topic::topic(topic&& other):
    _title{std::move(other._title)},
    _practices{std::move( other._practices )}
{
}

topic& operator=(topic const& other)
    _title{other._title},
    _practices{other._practices}
{
}

topic::topic& operator=(topic&& other)
    _title{std::move(other._title)},
    _practices{std::move( other._practices )}
{
}

std::string topic::title() const
{
    return _title;
}

void topic::add_practice(practice const& p)
{
    p.subtopic(std::make_shared<topic>(*this));
    _practices.push_back(p);
}

void topic::add_practice(practice&& p)
{
    p.subtopic(std::make_shared<topic>(*this));
    _practice.push_back(std::move(p));
}

std::vector<practice> topic::practices() const
{
    return _practices;
}

