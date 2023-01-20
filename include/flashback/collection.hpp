#pragma once

#include <flashback/practice.hpp>

namespace flashback
{

class collection
{
public:
    virtual std::vector<std::shared_ptr<practice>> collect_practices() = 0;
};

} // flashback
