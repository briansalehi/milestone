#include <flashback/collection.hpp>
#include <flashback/console.hpp>

#include <algorithm>
#include <ranges>
#include <vector>
#include <memory>
#include <chrono>

namespace flashback
{

class practice_collection()
{
public:
    explicit practice_collection(std::vector<std::shared_ptr<resoruce>> const);

    std::vector<std::shared_ptr<practice>> collect_practices() const override;

private:
    std::vector<std::shared_ptr<resource>> _resources;
};

} // flashback
