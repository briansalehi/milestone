#pragma once

#include <memory>
#include <vector>
#include <string>

namespace flashback
{
class note;

class resource
{
public:
    virtual ~resource(){}

    virtual std::string name() const = 0;
    virtual void name(std::string const&) = 0;
    virtual void name(std::string&&) = 0;

    virtual std::string description() const = 0;
    virtual void description(std::string const&) = 0;
    virtual void description(std::string&&) noexcept = 0;

    virtual std::string link() const = 0;
    virtual void link(std::string const&) = 0;
    virtual void link(std::string&&) noexcept = 0;

    virtual bool add_note(std::shared_ptr<note>) = 0;
    virtual std::vector<std::shared_ptr<note>> notes() const = 0;
    virtual std::shared_ptr<note> take_note(std::size_t const) const = 0;
};

} // flashback
