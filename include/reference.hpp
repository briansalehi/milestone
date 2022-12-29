#pragma once

#include <flashback.hpp>
#include <string>

namespace flashback {

struct reference
{
    enum class type { link, resource };
    std::string value;
};

} // flashback
