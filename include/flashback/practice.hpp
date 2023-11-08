#pragma once

#include <flashback/topic.hpp>
#include <flashback/reference.hpp>

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <compare>

namespace flashback {

class practice
{
public:
    practice(std::weak_ptr<topic>);

    practice(practice const&);
    practice(practice&&) noexcept;
    practice& operator=(practice const&);
    practice& operator=(practice&&) noexcept;

    std::string question() const;
    void question(std::string const&);
    void question(std::string&&) noexcept;

    std::string answer() const;
    void answer(std::string const&);
    void answer(std::string&&) noexcept;

    std::vector<reference> references() const;
    void add_reference(reference const&);
    void add_reference(reference&&) noexcept;

    std::vector<source> source() const;
    void add_source(source const&);
    void add_source(source&&) noexcept;

    std::chrono::days last_usage() const;
    void last_usage(std::chrono::days);
    void reset_usage();

    std::chrono::seconds elapsed_time() const;
    void elapsed_time(std::chrono::seconds);

    void subsection(std::weak_ptr<topic>);

    auto operator <=>(practice const&) = default;

private:
    std::string _question;
    std::string _answer;
    std::vector<origin> _origins;
    std::vector<reference> _references;
    std::weak_ptr<topic> _subtopic;
    std::chrono::days _last_usage;
    std::chrono::seconds _elapsed_time;
};

} // flashback
