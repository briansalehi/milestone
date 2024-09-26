#pragma once

namespace flashback
{
enum class publication_state
{
    open,
    writing,
    completed,
    revised,
    validated,
    approved,
    released,
    ignored
};

enum class block_type
{
    text,
    code
};
} // flashback
