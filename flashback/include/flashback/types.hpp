#pragma once

namespace flashback
{
enum class publication_state
{
    open,
    writing,
    completed,
    approved,
    released,
    ignored
};
} // flashback
