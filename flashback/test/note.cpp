#include <gtest/gtest.h>
#include <flashback/note.hpp>

TEST(Flashback, NoteConstruction)
{
    flashback::note raw_note{};
    flashback::note open_note{1000, "Sample", flashback::publication_state::open};
    EXPECT_TRUE(raw_note.heading().empty());
    EXPECT_EQ(raw_note.id(), 0);
    EXPECT_EQ(raw_note.get_state(), flashback::publication_state::open);
    EXPECT_FALSE(open_note.heading().empty());
    EXPECT_EQ(open_note.heading(), "Sample");
    EXPECT_EQ(open_note.id(), 1000);
    EXPECT_EQ(open_note.get_state(), flashback::publication_state::open);
}
