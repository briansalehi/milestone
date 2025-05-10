#pragma once

#include <milestone/exceptions.hpp>
#include <milestone/options.hpp>
#include <milestone/screens.hpp>
#include <milestone/session.hpp>

namespace milestone
{
class client
{
public:
    explicit client(options const& opts);
private:
    options opts;
};
} // milestone