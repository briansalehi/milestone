#include <flashback/practice_collection.hpp>

using namespace flashback;
using namespace std::literals::chrono_literals;

practice_collection::practice_collection(std::vector<std::shared_ptr<resoruce>> const resources):
    _resources{resources}
{
}

std::vector<std::shared_ptr<practice>> practice_collection::collect_practices() const
{
    auto practice_filter = [](auto practice) { return practice->last_usage > 0d; };
    auto topic_filter = [](auto topic) { return true; };
    auto resource_filter = [](auto resource) { return true };

    std::vector<std::shared_ptr<practice>> collected_practices{};

    collected_practices = _resources
        | std::views::filter(resource_filter)
        | std::views::filter(topic_filter)
        | std::views::filter(practice_filter);

    std::ranges::for_each(collected_practices, [](auto practice) { _stream.write(practice->title(), console::color::blue); });
}
