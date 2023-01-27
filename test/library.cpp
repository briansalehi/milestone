#include <flashback/library.hpp>
#include <gtest/gtest.h>

TEST(Library, Construction)
{
    flashback::library library{"postgres://postgres@localhost/flashback_test"};

    EXPECT_EQ(library.count(), 40);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
