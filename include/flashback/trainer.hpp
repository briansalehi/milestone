#pragma once

#include <flashback/note.hpp>
#include <flashback/space.hpp>
#include <flashback/console.hpp>
#include <flashback/practice.hpp>

#include <memory>
#include <queue>

namespace flashback
{

///
/// \brief A space to practice subjects by answering questions and comparing your answers.
///
class trainer: public space
{
public:
    trainer();

    void init() override;

private:
    console _stream;
    std::queue<std::shared_ptr<practice>> _practice_queue;
};

} // flashback
