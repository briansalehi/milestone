#include <flashback/library.hpp>
#include <gtest/gtest.h>

TEST(Library, Initialization)
{
    flashback::library library{"postgres://postgres@localhost/flashback_test"};

    library.init();
    EXPECT_EQ(1, 1);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
