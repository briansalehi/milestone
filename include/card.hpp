#pragma once

#include <regex>
#include <string>

namespace flashback
{
// temporary type aliases
using checksum = std::string;
using resource = std::ostringstream;
using details = std::ostringstream;
using heading = std::string;

enum class card_type { informative, interactive };

class card
{
public:
    explicit card(std::stringstream&);

private:
    checksum id;
    details body;
    heading header;
    resource resources;
    card_type type;
}; // card
} // flashback
