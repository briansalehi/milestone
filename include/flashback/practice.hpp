#pragma once

#include <vector>
#include <string>
#include <sstream>

namespace flashback
{

class flashcard
{
public:
    explicit practice(std::ostringstream const&) = default;
    practice(practice const&);
    practice& operator=(practice const&);
    practice(practice&&) noexcept;
    practice& operator=(practice&&) noexcept;
    virtual ~practice();

protected:
    virtual void parse_stream();

private:
    std::string title;
    std::string body;
    std::vector<std::string> resources;
    std::vector<std::string> references;
};

} // flashback
