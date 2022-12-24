#include <gtest/gtest.h>
#include <note.hpp>

#include <string>

TEST(NoteTest, ConstructionTest)
{
    using namespace std::literals::string_literals;

    flashback::note note{false, "title"s, "description"s};

    EXPECT_EQ(note.title, "title"s);
    EXPECT_EQ(note.description, "description"s);
    EXPECT_EQ(note.collected, false);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
