#pragma once

#include <string>
#include <vector>

namespace flashback
{

class note
{
public:
    note();
    explicit note(std::string const& title, std::string const& description, std::string const& position, bool const collected);

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

    bool operator<(note const&);
    bool operator!=(note const&);

private:
    std::string _title;
    std::string _description;
    std::string _position;
    bool _collected;
};

} // flashback
