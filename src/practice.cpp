#include <flashback/practice.hpp>
#include <flashback/reference.hpp>
#include <flashback/source.hpp>

using namespace flashback;
using namespace std::literals::chrono_literals;

practice::practice(unsigned long int const id):
    _id{id}, _question{}, _answer{}, _references{}
{
}

practice::practice(practice const& other):
    _question{other.question()},
    _answer{other.answer()},
    _references{}
{
    std::ranges::copy(other._references, std::back_inserter(_references));
}

practice::practice(practice&& other) noexcept :
    _question{std::move(other.question())},
    _answer{std::move(other.answer())},
    _references{}
{
    std::ranges::move(other._references, std::back_inserter(_references));
}

practice& practice::operator=(practice const& other)
{
    _question = other._question;
    _answer = other._answer;
    std::ranges::copy(other._references, std::back_inserter(_references));

    return *this;
}

practice& practice::operator=(practice&& other) noexcept
{
    _question = other._question;
    _answer = other._answer;
    std::ranges::move(other._references, std::back_inserter(_references));

    return *this;
}

unsigned long int practice::id() const
{
    return _id;
}

std::string practice::question() const
{
    return _question;
}

void practice::question(std::string const& question)
{
    _question = question;
}

void practice::question(std::string&& question)
{
    _question = std::move(question);
}

std::string practice::answer() const
{
    return _answer;
}

void practice::answer(std::string const& answer)
{
    _answer = answer;
}

void practice::answer(std::string&& answer)
{
    _answer = std::move(answer);
}

std::vector<std::shared_ptr<reference>> practice::references() const
{
    return _references;
}

void practice::add_reference(std::shared_ptr<reference> ref)
{
    _references.push_back(ref);
}

/*
std::vector<source> practice::soruces() const
{
    return _sources;
}

void practice::add_source(std::shared_ptr<source> origin)
{
    _sources.push_back(origin);
}
*/

std::chrono::days practice::last_usage() const
{
    return std::chrono::duration_cast<std::chrono::days>(std::chrono::steady_clock::now() - _last_usage);
}

void practice::reset_usage()
{
    _last_usage -= _last_usage.time_since_epoch();
}

std::chrono::seconds practice::elapsed_time() const
{
    return _elapsed_time;
}

void practice::elapsed_time(std::chrono::seconds const elapsed_time)
{
    _elapsed_time = elapsed_time; 
}
    
bool practice::operator==(practice const& other)
{
    return _id == other.id();
}

bool practice::operator<(practice const& other)
{
    return last_usage() < other.last_usage();
}
