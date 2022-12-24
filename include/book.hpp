#pragma once

#include <resource.hpp>

#include <vector>
#include <string>
#include <tuple>

namespace flashback
{
// forward declaration
class resource;
class note;

class book: public resource
{
public:
    book() = default;
    explicit book(std::string const&, unsigned int const);
    book(book const&);
    book(book&&) noexcept;
    book& operator=(book const&);
    book& operator=(book&&) noexcept;

    std::string title() const override;
    void title(std::string const&) override;
    void title(std::string&&) noexcept override;

    std::vector<note> notes() const override;
    bool add_note(note const&) override;
    bool add_note(note&&) noexcept override;

    unsigned int chapters() const;
    void chapters(unsigned int const);

private:
    std::string _title;
    std::vector<note> _notes;
    unsigned int _chapters;
};

} // flashback
