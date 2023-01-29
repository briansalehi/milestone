#include <flashback/subject.hpp>

using namespace flashback;

subject::subject(unsigned long int const id): _id{id}, _title{}, _topics{}
{
}

subject::subject(unsigned long int const id, std::string const& title):
    _id{id}, _title{title}, _topics{}
{
}

unsigned long int subject::id() const
{
    return _id;
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
    return _id == other.id();
}

bool subject::operator<(subject const& other) const
{
    return _id == other.id(); // this needs to be replaced by creation_date
}
