#pragma once

#include <flashback/resource.hpp>
#include <flashback/note.hpp>

#include <memory>
#include <vector>
#include <string>
#include <tuple>

namespace flashback
{

///
/// \brief A Concrete Implementation of Resource
///
/// Books are one of the most common resources used by learners to become knowledged
/// in a specific domain.\n
/// This implementation tries to hold the information of this kind of resource,
/// but not in every detail.
///
/// This implementation of book is limited to following items:
///
/// * Title of the book
/// * Number of chapters
/// * Notes of the book
///
/// There are two ways of creating an object though:
///
/// * By giving the contents of a markdown file
/// * By filling the object with database results
///
/// For first development steps, the former is used.
///
/// But for creating an object of this class using markdown file content,
/// the builder pattern is required because of step by step building process
/// of the object as the content of the file will be read line by line.
///
/// \see resource_builder
///
class book: public resource
{
public:
    book() = default;
    explicit book(std::ostringstream&);
    explicit book(std::string const&, unsigned int const);
    book(book const&);
    book(book&&) noexcept;
    book& operator=(book const&);
    book& operator=(book&&) noexcept;

    std::string title() const override;
    void title(std::string const&) override;
    void title(std::string&&) noexcept override;

    std::vector<std::shared_ptr<note>> notes() const override;
    bool add_note(std::shared_ptr<note>) override;

    unsigned int chapters() const;
    void chapters(unsigned int const);

private:
    std::string _title;
    std::vector<std::shared_ptr<note>> _notes;
    unsigned int _chapters;
};

} // flashback
