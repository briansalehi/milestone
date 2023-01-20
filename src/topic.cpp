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

bool topic::add_practice(std::shared_ptr<practice> input_practice)
{
    _practices.push_back(input_practice);
    return true;
}

std::vector<std::shared_ptr<practice>> topic::practices() const
{
    return _practices;
}

std::vector<std::shared_ptr<practice>> topic::candidates(std::size_t amount)
{
    std::vector<std::shared_ptr<practice>> buffer;

    std::ranges::sort(_practices);
    std::copy_n(_practices.begin(), amount, buffer.begin());

    return buffer;
}
