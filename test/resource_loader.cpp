#include <flashback/resource_loader.hpp>
#include <gtest/gtest.h>

TEST(ResourceLoader, Construction)
{
    flashback::resource_loader loader("postgres://postgres@localhost/flashback_test");

    EXPECT_EQ(loader.resources().size(), 0);
}

TEST(ResourceLoader, Connection)
{
    flashback::resource_loader loader("postgres://postgres@localhost/flashback_test");

    EXPECT_EQ(loader.connected(), true);
}

TEST(ResourceLoader, Fetching)
{
    flashback::resource_loader loader("postgres://postgres@localhost/flashback_test");
    loader.fetch_content();

    EXPECT_EQ(loader.resources().size(), 40);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
