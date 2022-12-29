#include <book.hpp>
#include <gtest/gtest.h>

#include <memory>
#include <string>

using namespace std::literals::string_literals;

TEST(BookTest, DefaultConstructionTest)
{
    flashback::book origin{};

    EXPECT_EQ(origin.title().empty(), true);
    EXPECT_EQ(origin.notes().empty(), true);
    EXPECT_EQ(origin.chapters(), 0);
}

TEST(BookTest, OverloadedConstructionTest)
{
    flashback::book book{"sample"s, 42};

    EXPECT_EQ(book.title(), "sample"s);
    EXPECT_EQ(book.notes().empty(), true);
    EXPECT_EQ(book.chapters(), 42);
}

TEST(BookTest, CopyConstructionTest)
{
    flashback::book origin{"sample"s, 21};
    flashback::book copy{origin};

    EXPECT_EQ(origin.title(), "sample"s);
    EXPECT_EQ(origin.notes().empty(), true);
    EXPECT_EQ(origin.chapters(), 21);
    EXPECT_EQ(copy.title(), "sample"s);
    EXPECT_EQ(copy.notes().empty(), true);
    EXPECT_EQ(copy.chapters(), 21);
}

TEST(BookTest, MoveConstructionTest)
{
    flashback::book origin{"sample"s, 21};
    flashback::book copy{std::move(origin)};

    EXPECT_EQ(origin.title().empty(), true);
    EXPECT_EQ(origin.notes().empty(), true);
    EXPECT_EQ(origin.chapters(), 0);
    EXPECT_EQ(copy.title(), "sample"s);
    EXPECT_EQ(copy.notes().empty(), true);
    EXPECT_EQ(copy.chapters(), 21);
}

TEST(BookTest, TitleTest)
{
    flashback::book origin{"sample"s, 21};

    EXPECT_EQ(origin.title(), "sample"s);
}

TEST(BookTest, AddTitleTest)
{
    flashback::book origin;
    origin.title("sample"s);

    EXPECT_EQ(origin.title(), "sample"s);
}

TEST(BookTest, NotesTest)
{
    flashback::book origin;
    origin.add_note(std::make_shared<flashback::note>("title"s, "description"s, "position"s, false));

    ASSERT_EQ(origin.notes().size(), 1);
    EXPECT_EQ(origin.notes().back()->title, "title"s);
}

TEST(BookTest, ChaptersTest)
{
    flashback::book origin{"sample"s, 21};

    EXPECT_EQ(origin.chapters(), 21);
}

TEST(BookTest, AddChaptersTest)
{
    flashback::book origin;
    origin.chapters(21);

    EXPECT_EQ(origin.chapters(), 21);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
