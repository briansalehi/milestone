#include <gtest/gtest.h>
#include <flashback/flashback.hpp>

TEST(Flashback, Construct)
{
    flashback::database database{};
    ASSERT_EQ(true, true);
}
