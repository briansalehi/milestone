#include <flashback/practice_collection.hpp>

using namespace flashback;
using namespace std::literals::chrono_literals;

practice_collection::practice_collection(std::vector<std::shared_ptr<practice>> const practices):
    _practices{practices},
    _console{std::cerr, std::cin}
{
}

std::vector<std::shared_ptr<practice>> practice_collection::collect_practices()
{
    return _practices;
}
