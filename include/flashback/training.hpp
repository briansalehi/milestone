#pragma once

#include <flashback/note.hpp>
#include <flashback/space.hpp>
#include <flashback/console.hpp>
#include <flashback/practice.hpp>

#include <pqxx/pqxx>

#include <memory>
#include <chrono>
#include <string>
#include <queue>
#include <map>

namespace flashback
{

///
/// \brief A space to practice subjects by answering questions and comparing your answers.
///
class training: public space
{
public:
    using color = console<std::istream, std::ostream>::color;
    using style = console<std::istream, std::ostream>::style;

    training();

    void init() override;

protected:
    virtual char prompt_space_actions() override;
    virtual void perform_space_actions() override;

private:
    std::size_t get_record_id(pqxx::result const&);

    void start_practice_session();
    void practice_subject();

    char prompt_practice_actions();
    void perform_practice_actions(std::shared_ptr<practice>);

    void mark_practice_solved(std::shared_ptr<practice>);
    void print_practice_answer(std::shared_ptr<practice>);

private:
    pqxx::connection _connection;
    console<std::istream, std::ostream> _stream;
    std::vector<std::shared_ptr<practice>> _practice_queue;
    std::chrono::time_point<std::chrono::steady_clock> _practice_start_time;
};

} // flashback
