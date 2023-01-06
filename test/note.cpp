#include <gtest/gtest.h>
#include <flashback/note.hpp>

#include <string>

using namespace std::literals::string_literals;

TEST(Note, Title)
{
    flashback::note note;
    note.title("title"s);

    EXPECT_EQ(note.title(), "title"s);
}

TEST(Note, Description)
{
    flashback::note note;
    note.description("description"s);

    EXPECT_EQ(note.description(), "description"s);
}

TEST(Note, Position)
{
    flashback::note note;
    note.position("position"s);

    EXPECT_EQ(note.position(), "position"s);
}

TEST(Note, Collected)
{
    flashback::note note;
    note.collected(true);
    EXPECT_EQ(note.collected(), true);

    note.collected(false);
    EXPECT_EQ(note.collected(), false);
}

TEST(Note, Construction)
{
    flashback::note note{"title"s, "description"s, "position", false};

    EXPECT_EQ(note.title(), "title"s);
    EXPECT_EQ(note.description(), "description"s);
    EXPECT_EQ(note.position(), "position"s);
    EXPECT_EQ(note.collected(), false);
}

TEST(Note, LowerOperation)
{
    flashback::note note1{"title"s, "description"s, "chapter 1 page 24", false};
    flashback::note note2{"title"s, "description"s, "chapter 2 page 53", false};

    EXPECT_EQ(note1 < note2, true);
}

TEST(Note, InequalityOperation)
{
    flashback::note note1{"title"s, "description"s, "chapter 1 page 24", false};
    flashback::note note2{"title"s, "description"s, "chapter 2 page 53", false};

    EXPECT_EQ(note1 != note2, true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
