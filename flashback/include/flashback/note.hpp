#pragma once

#include <flashback/types.hpp>
#include <string>
#include <string_view>
#include <vector>
#include <ranges>
#include <algorithm>

namespace flashback
{
template<typename CharType>
class basic_note
{
    std::size_t note_id;
    std::basic_string<CharType> note_heading;
    publication_state note_state;

public:
    basic_note() : note_id{}, note_heading{}, note_state{}
    {
    }

    explicit basic_note(std::size_t const id, std::basic_string<CharType> const& heading, publication_state const state) :
        note_id{id}
        , note_heading{heading}
        , note_state{state}
    {
    }

    std::size_t id() const noexcept
    {
        return note_id;
    }

    std::basic_string<CharType> heading() const noexcept
    {
        return note_heading;
    }

    publication_state get_state() const noexcept
    {
        return note_state;
    }
};

using note = basic_note<char>;
using wnote = basic_note<wchar_t>;
using note8 = basic_note<char8_t>;
using note16 = basic_note<char16_t>;
using note32 = basic_note<char32_t>;
} // flashback
