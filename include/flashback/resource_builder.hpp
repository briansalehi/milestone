#pragma once

#include <flashback/resource.hpp>

#include <sstream>
#include <memory>

namespace flashback
{

///
/// \brief Builder Pattern Implementation for Resources
///
/// The [builder pattern](https://refactoring.guru/design-patterns/builder)
/// is implemented for building resources here because resources such as books
/// and courses have many constituents which should be build step by step.
///
class resource_builder
{
public:
    virtual ~resource_builder(){}

    virtual void reset() = 0;
    virtual std::shared_ptr<resource> result() const = 0;

    virtual void read_title(std::stringstream&) const = 0;
    virtual void read_chapters(std::stringstream&) const = 0;

protected:
    virtual void read_note(std::stringstream&, std::string const&) const = 0;
};

} // flashback
