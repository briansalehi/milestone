#pragma once

#include <flashback/resource.hpp>

#include <sstream>
#include <vector>
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
    virtual void reset() = 0;
    virtual std::shared_ptr<resource> result() const = 0;

    virtual void read_title(std::ostringstream&) = 0;
    virtual std::vector<std::shared_ptr<note>> read_chapter(std::ostringstream&) = 0;

protected:
    virtual std::shared_ptr<note> read_note(std::ostringstream&) = 0;
};

} // flashback
