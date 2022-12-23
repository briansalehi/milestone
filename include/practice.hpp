#pragma once

#include <string>
#include <vector>

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

    std::vector<reference> references() const;
    void add_reference(reference const&);
    void add_reference(reference&&);

    std::vector<resource> resoruces() const;
    void add_resource(resource const&);
    void add_resource(resource&&);
    
    // operators
    bool operator==(practice const&);

private:
    std::string _question;
    std::string _answer;
    std::vector<reference> _references;
    std::vector<resource> _resources;
};

} // flashback
