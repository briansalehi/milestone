#include <gtest/gtest.h>
#include <flashback/note.hpp>

#include <string>

using namespace std::literals::string_literals;

TEST(NoteTest, ConstructionTest)
{
    flashback::note note{"title"s, "description"s, "position", false};

    EXPECT_EQ(note.title, "title"s);
    EXPECT_EQ(note.description, "description"s);
    EXPECT_EQ(note.position, "position"s);
    EXPECT_EQ(note.collected, false);
}

TEST(NoteTest, LowerOperationTest)
{
    flashback::note note1{"title"s, "description"s, "chapter 1 page 24", false};
    flashback::note note2{"title"s, "description"s, "chapter 2 page 53", false};

    EXPECT_EQ(note1 < note2, true);
}

TEST(NoteTest, InequalityOperationTest)
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
