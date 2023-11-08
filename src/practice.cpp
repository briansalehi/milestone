#include <flashback/practice.hpp>

using namespace flashback;

practice::practice(std::weak_ptr<topic> subtopic):
    _question{},
    _answer{},
    _origins{},
    _references{},
    _subtopic{subtopic},
    _last_usage{},
    _elapsed_time{}
{
    if (!subtopic)
    {
        throw std::bad_weak_ptr{"invalid subtopic assigned to practice"};
    }
}

practice::practice(practice const& other):
    _question{other._question},
    _answer{other._answer},
    _origins{other._origins},
    _references{other._references},
    _subtopic{other._subtopic},
    _last_usage{other._last_usage},
    _elapsed_time{other._elapsed_time}
{
}

practice::practice(practice&& other)
    _question{std::move( other._question )},
    _answer{std::move( other._answer )},
    _origins{std::move(others._origins)},
    _references{std::move(other._references)},
    _subtopic{std::move( other._subtopic)},
    _last_usage{std::move( other._last_usage )},
    _elapsed_time{std::move( other._elapsed_time )}
{
}

practice::practice& operator=(practice const&)
{
    _question = other._question;
    _answer = other._answer;
    _origins = other._origins;
    _references = other._references;
    _subtopic = other._subtopic;
    _last_usage = other._last_usage;
    _elapsed_time = other._elapsed_time;
}

practice::practice& operator=(practice&& other)
{
    _question = std::move(other._question);
    _answer = std::move(other._answer);
    _origins = std::move(other._origins);
    _references = std::move(other._references);
    _subtopic = std::move(other._subtopic);
    _last_usage = std::move(other._last_usage);
    _elapsed_time = std::move(other._elapsed_time);
}

std::string practice::question() const
{
    return _question;
}

void practice::question(std::string const& q)
{
    _question = q;
}

void practice::question(std::string&& q)
{
    _question = std::move(q);
}

std::string practice::answer() const
{
    return _answer;
}

void practice::answer(std::string const& a)
{
    _answer = a;
}

void practice::answer(std::string&& a)
{
    _answer = std::move(a);
}

std::vector<reference> practice::references() const
{
    return _references;
}

void practice::add_reference(reference const& r)
{
    _references.push_back(r);
}

void practice::add_reference(reference&& r)
{
    _references.push_back(std::move(r));
}

std::vector<source> practice::source() const
{
    return _sources;
}

void practice::add_source(source const& s)
{
    _sources.push_back(s);
}

void practice::add_source(source&& s)
{
    _sources.push_back(std::move(s));
}

void practice::subsection(std::weak_ptr<topic> p)
{
    _subtopic.reset(p);
}

std::chrono::days practice::last_usage() const
{
    return _last_usage;
}

void practice::last_usage(std::chrono::days days)
{
    _last_usage = days;
}

void practice::reset_usage()
{
    _last_usage = 0;
}

std::chrono::seconds practice::elapsed_time() const
{
    return _elapsed_time;
}

void practice::elapsed_time(std::chrono::seconds seconds)
{
    _elapsed_time = seconds;
}

