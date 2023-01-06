#include <flashback/markdown_note_builder.hpp>
#include <gtest/gtest.h>

#include <sstream>
#include <memory>
#include <string>

using namespace std::literals::string_literals;

TEST(NoteBuilder, Construction)
{
    flashback::markdown_note_builder builder{};
    EXPECT_EQ(builder.result() == nullptr, false);

    builder.reset();
    EXPECT_EQ(builder.result() == nullptr, false);
}

TEST(NoteBuilder, SingleLineTitle)
{
    std::string title{"Single Line Title"};
    std::stringstream buffer;
    flashback::markdown_note_builder builder{};

    buffer << "<summary>" << title << "</summary>";
    builder.read_title(buffer);
    EXPECT_EQ(builder.result()->title(), title);
}

TEST(NoteBuilder, MultiLineTitle)
{
    std::string title{"Multi Line Title"};
    std::stringstream buffer;
    flashback::markdown_note_builder builder{};

    buffer << "<summary>" << title << "</summary>";
    builder.read_title(buffer);
    EXPECT_EQ(builder.result()->title(), title);
}

TEST(NoteBuilder, Descriptions)
{
    flashback::markdown_note_builder builder{};

    std::stringstream buffer;
    buffer << "Some description to test";
    buffer << "in multiple lines";

    builder.read_description(buffer);
    EXPECT_EQ(builder.result()->description(), buffer.str());
}

TEST(NoteBuilder, Position)
{
    flashback::markdown_note_builder builder{};

    std::stringstream buffer;

    builder.read_references(buffer);
    EXPECT_EQ(builder.result()->position().empty(), true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
