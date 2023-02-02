#pragma once

#include <flashback/reference.hpp>

#include <string>
#include <vector>
#include <memory>
#include <chrono>

namespace flashback {

// forward declaration
class reference;
class resource;

class practice
{
public:
    explicit practice(unsigned long int const);

    practice(practice const&);
    practice(practice&&) noexcept;
    practice& operator=(practice const&);
    practice& operator=(practice&&) noexcept;

    unsigned long int id() const;

    std::string question() const;
    void question(std::string const&);
    void question(std::string&&);

    std::string answer() const;
    void answer(std::string const&);
    void answer(std::string&&);

    std::vector<std::shared_ptr<reference>> references() const;
    void add_reference(std::shared_ptr<reference>);

    /*
    std::vector<std::shared_ptr<source>> source() const;
    void add_source(std::shared_ptr<source>);
    */

    std::chrono::days last_usage() const;
    void last_usage(std::chrono::days const);
    void reset_usage();

    std::chrono::seconds elapsed_time() const;
    void elapsed_time(std::chrono::seconds const);
    
    // operators
    bool operator==(practice const&);
    bool operator<(practice const&);

private:
    unsigned long int _id;
    std::string _question;
    std::string _answer;
    std::vector<std::shared_ptr<reference>> _references;
    std::chrono::days _last_usage;
    std::chrono::seconds _elapsed_time;
};

} // flashback
