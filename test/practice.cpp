#include <gtest/gtest.h>
#include <flashback/practice.hpp>

TEST(PracticeTest, ConstructionTests)
{
    flashback::practice default_constructed;
    ASSERT_EQ(default_constructed.question().empty(), true);
}

TEST(PracticeTest, CopyConstructionTest)
{
    flashback::practice default_constructed;
    flashback::practice copy_constructed(default_constructed);
    ASSERT_EQ(copy_constructed.question().empty(), true);
}

TEST(PracticeTest, MoveConstructionTest)
{
    flashback::practice move_constructed(flashback::practice{});
    ASSERT_EQ(move_constructed.question().empty(), true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
