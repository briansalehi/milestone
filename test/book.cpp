#include <book.hpp>
#include <gtest/gtest.h>

TEST(BookTest, DefaultConstructionTest)
{
    flashback::book origin{};

    EXPECT_EQ(origin.title().empty(), true);
    EXPECT_EQ(origin.notes().empty(), true);
    EXPECT_EQ(origin.chapters(), 0);
}

TEST(BookTest, OverloadedConstructionTest)
{
    flashback::book book{"sample", 42};

    EXPECT_EQ(book.title(), "sample");
    EXPECT_EQ(book.notes().empty(), true);
    EXPECT_EQ(book.chapters(), 42);
}

TEST(BookTest, CopyConstructionTest)
{
    flashback::book origin{"sample", 21};
    flashback::book copy{origin};

    EXPECT_EQ(origin.title(), "sample");
    EXPECT_EQ(origin.notes().empty(), true);
    EXPECT_EQ(origin.chapters(), 21);
    EXPECT_EQ(copy.title(), "sample");
    EXPECT_EQ(copy.notes().empty(), true);
    EXPECT_EQ(copy.chapters(), 21);
}

TEST(BookTest, MoveConstructionTest)
{
    flashback::book origin{"sample", 21};
    flashback::book copy{std::move(origin)};

    EXPECT_EQ(origin.title().empty(), true);
    EXPECT_EQ(origin.notes().empty(), true);
    EXPECT_EQ(origin.chapters(), 0);
    EXPECT_EQ(copy.title(), "sample");
    EXPECT_EQ(copy.notes().empty(), true);
    EXPECT_EQ(copy.chapters(), 21);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
