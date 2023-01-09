#include <flashback/topic.hpp>

using namespace flashback;

topic::topic(): _title{}, _practices{}
{
}

topic::topic(std::string const& title): _title{title}, _practices{}
{
}

std::string topic::title() const
{
    return _title;
}

void topic::title(std::string const& title)
{
    _title = title;
}

void topic::title(std::string&& title)
{
    _title = std::move(title);
}

bool topic::add_practice(std::shared_ptr<practice> incomplete_practice)
{
    bool success;
    std::tie(std::ignore, success) = _practices.insert(incomplete_practice);
    return success;
}

std::set<std::shared_ptr<practice>> topic::practices() const
{
    return _practices;
}

