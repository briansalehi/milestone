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

    virtual std::string name() const = 0;
    virtual void name(std::string const&) = 0;
    virtual void name(std::string&&) = 0;

    virtual std::string description() const;
    virtual void description(std::string const&);
    virtual void description(std::string&&) noexcept;

    virtual std::string link() const;
    virtual void link(std::string const&);
    virtual void link(std::string&&) noexcept;

    virtual bool add_note(std::shared_ptr<note>) = 0;
    virtual std::vector<std::shared_ptr<note>> notes() const = 0;
    virtual std::shared_ptr<note> take_note(std::size_t const) const = 0;
};

} // flashback
