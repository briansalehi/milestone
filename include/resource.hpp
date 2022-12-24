#pragma once

#include <note.hpp>

#include <vector>
#include <string>

namespace flashback
{

class resource
{
public:
    virtual std::string title() const = 0;
    virtual void title(std::string const&) = 0;
    virtual void title(std::string&&) = 0;

    virtual std::vector<note> notes() const = 0;
    virtual bool add_note(note const&) = 0;
    virtual bool add_note(note&&) noexcept = 0;
};

} // flashback
