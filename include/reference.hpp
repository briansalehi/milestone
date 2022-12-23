#pragma once

namespace flashback {

struct reference
{
    enum class type { link, resource };
    std::string value;
};

} // flashback
