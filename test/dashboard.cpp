#include <flashback/dashboard.hpp>
#include <gtest/gtest.h>

TEST(Dashboard, Construction)
{
    flashback::dashboard dashboard{};

    EXPECT_EQ(dashboard.space_names().size(), 4);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
