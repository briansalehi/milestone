#pragma once

#include <flashback/reference.hpp>

#include <string>
#include <vector>
#include <memory>

namespace flashback {

// forward declaration
class reference;
class resource;

class practice
{
public:
    explicit practice();
    practice(practice const&);
    practice(practice&&) noexcept;
    practice& operator=(practice const&);
    practice& operator=(practice&&) noexcept;

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
    
    // operators
    bool operator==(practice const&);

private:
    std::string _question;
    std::string _answer;
    std::vector<std::shared_ptr<reference>> _references;
};

} // flashback
