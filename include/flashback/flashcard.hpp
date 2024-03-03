#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <format>

namespace flashback
{

class flashcard
{
public:
    flashcard(std::stringstream&);
    flashcard(flashcard const&);
    flashcard& operator=(flashcard const&);
    flashcard(flashcard&&) noexcept;
    flashcard& operator=(flashcard&&) noexcept;
    virtual ~flashcard() = default;

protected:
    virtual void parse_stream(std::stringstream&);
    virtual void parse_title(std::string const&);
    virtual void parse_body(std::stringstream&);
    virtual void parse_resources(std::stringstream&);
    virtual void parse_references(std::stringstream&);

public:
    std::string title;
    std::string body;
    std::vector<std::string> resources;
    std::vector<std::string> references;
};

} // flashback
