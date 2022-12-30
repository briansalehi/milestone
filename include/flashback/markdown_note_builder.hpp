#pragma once

#include <flashback/note_builder.hpp>

namespace flashback
{

class markdown_note_builder final : public note_builder
{
public:
    markdown_note_builder();

    markdown_note_builder(markdown_note_builder const&) = delete;
    markdown_note_builder& operator=(markdown_note_builder const&) = delete;
    markdown_note_builder(markdown_note_builder&&) = delete;
    markdown_note_builder& operator=(markdown_note_builder&&) = delete;

    virtual void reset() override;
    virtual std::shared_ptr<note> result() const override;

    virtual void read_title(std::stringstream&) const override;
    virtual void read_description(std::stringstream&) const override;
    virtual void read_references(std::stringstream&) const override;

private:
    std::shared_ptr<note> _note;
};

} // flashback
