#pragma once

#include <flashback/note.hpp>

#include <sstream>
#include <string>
#include <memory>

namespace flashback
{

///
/// \brief Builder Pattern Implementation of Notes
///
/// Constructing objects and filling them by data being read from a file
/// is inherently sequencial and step by step.\n
/// [Builder Pattern](https://refactoring.guru/design-patterns/builder) is
/// here implemented to construct note objects step by step.\n
/// This pattern is also commonly used to create objects with common functionality
/// but with various representations of the object.\n
/// Here notes might be book notes or course notes, or any other future designed resources.
///
class note_builder
{
public:
    virtual ~note_builder(){}

    virtual void reset() = 0;
    virtual std::shared_ptr<note> result() const = 0;

    virtual void read_title() const = 0;
    virtual void read_description() const = 0;
    virtual void read_references() const = 0;
};

} // flashback
