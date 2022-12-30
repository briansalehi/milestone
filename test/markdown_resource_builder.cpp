#include <flashback/markdown_resource_builder.hpp>
#include <gtest/gtest.h>

TEST(ResourceBuilder, Construction)
{
    flashback::markdown_resource_builder builder{};
    EXPECT_EQ(builder.result() == nullptr, false);

    builder.reset();
    EXPECT_EQ(builder.result() == nullptr, false);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
