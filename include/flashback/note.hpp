#pragma once

#include <string>
#include <vector>

namespace flashback
{

class note
{
public:
    explicit note(unsigned long int const);

    unsigned long int id() const;

    std::string title() const;
    void title(std::string const&);
    void title(std::string&&) noexcept;

    std::string description() const;
    void description(std::string const&);
    void description(std::string&&) noexcept;

    std::string position() const;
    void position(std::string const&);
    void position(std::string&&) noexcept;

    bool collected() const;
    void collected(bool const);

    bool collectable() const;
    void collectable(bool const);

    bool operator<(note const&);
    bool operator!=(note const&);

private:
    unsigned long int _id;
    std::string _title;
    std::string _description;
    std::string _position;
    bool _collectable;
    bool _collected;
};

} // flashback
