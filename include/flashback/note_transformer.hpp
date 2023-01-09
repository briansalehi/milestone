#pragma once

#include <flashback/transformer.hpp>

namespace flashback
{

class note_transformer: public transformer
{
public:
    virtual void extract() const override;

private:
};

} // flashback
