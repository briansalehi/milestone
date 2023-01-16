#pragma once

#include <flashback/note.hpp>

#include <memory>
#include <vector>
#include <string>

namespace flashback
{

class resource
{
public:
    virtual ~resource(){}

    virtual std::string title() const = 0;
    virtual void title(std::string const&) = 0;
    virtual void title(std::string&&) = 0;

    virtual bool add_note(std::shared_ptr<note>) = 0;
    virtual std::vector<std::shared_ptr<note>> notes() const = 0;
    virtual std::shared_ptr<note> take_note(std::size_t const) const = 0;
};

} // flashback
