#pragma once

namespace flashback
{

///
/// \brief A space to practice subjects by answering questions and comparing your answers.
///
class trainer: public space
{
public:
    void import(std::shared_ptr<note>);

private:
};

} // flashback
