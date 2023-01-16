#include <flashback/subject.hpp>

using namespace flashback;

subject::subject() : _title{}, _topics{}
{
}

subject::subject(std::string const& title) : _title{title}, _topics{}
{
}

std::string subject::title() const
{
    return _title;
}

void subject::title(std::string const& title)
{
    _title = title;
}

void subject::title(std::string&& title)
{
    _title = std::move(title);
}

bool subject::add_topic(std::shared_ptr<topic> input)
{
    if (input)
    {
        _topics.push_back(input);
        return true;
    }

    return false;
}

std::vector<std::shared_ptr<topic>> subject::topics() const
{
    return _topics;
}

std::queue<std::shared_ptr<practice>> subject::queue_practices() const
{
    std::queue<std::shared_ptr<practice>> practice_queue{};

    return practice_queue;
}

bool subject::operator==(subject const& other) const
{
    return _title == other.title();
}

bool subject::operator<(subject const& other) const
{
    return _title < other.title();
}
