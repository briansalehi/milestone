#include <gtest/gtest.h>
#include <flashback/note.hpp>

TEST(Flashback, NoteConstruction)
{
    constexpr int note_id{1000};
    flashback::note raw_note{};
    flashback::note open_note{note_id, "Sample", flashback::publication_state::open};
    EXPECT_TRUE(raw_note.heading().empty());
    EXPECT_EQ(raw_note.id(), 0);
    EXPECT_EQ(raw_note.get_state(), flashback::publication_state::open);
    EXPECT_FALSE(open_note.heading().empty());
    EXPECT_EQ(open_note.heading(), "Sample");
    EXPECT_EQ(open_note.id(), note_id);
    EXPECT_EQ(open_note.get_state(), flashback::publication_state::open);
}
