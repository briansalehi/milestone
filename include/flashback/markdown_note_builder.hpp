#pragma once

#include <flashback/note_builder.hpp>

#include <fstream>
#include <memory>

namespace flashback
{

class markdown_note_builder final : public note_builder
{
public:
    explicit markdown_note_builder(std::ifstream&);
    virtual ~markdown_note_builder();

    virtual void reset() override;
    virtual std::shared_ptr<note> result() const override;

    virtual void read_title() const override;
    virtual void read_description() const override;
    virtual void read_references() const override;

private:
    std::ifstream& _buffer;
    std::shared_ptr<note> _note;
};

} // flashback
