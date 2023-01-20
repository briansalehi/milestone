#include <flashback/collection.hpp>
#include <flashback/practice.hpp>
#include <flashback/console.hpp>

#include <algorithm>
#include <ranges>
#include <vector>
#include <memory>
#include <chrono>

namespace flashback
{

class practice_collection: public collection
{
public:
    explicit practice_collection(std::vector<std::shared_ptr<practice>> const);

    std::vector<std::shared_ptr<practice>> collect_practices() override;

private:
    console _console;
    std::vector<std::shared_ptr<practice>> _practices;
};

} // flashback
