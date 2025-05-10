#include <milestone/client.hpp>

using namespace milestone;

client::client(options const& opts) : opts{opts}
{
    screens screen{};
    session session{};
    screen.print(0, 0, "Milestone");
}