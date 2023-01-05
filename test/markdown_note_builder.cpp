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

    buffer << "<summary>" << title << "</summary>\n";
    builder.read_title(buffer);
    EXPECT_EQ(builder.result()->title, title);
}

TEST(NoteBuilder, MultiLineTitle)
{
    std::string title{"Multi Line Title"};
    std::stringstream buffer;
    flashback::markdown_note_builder builder{};

    buffer << "<summary>\n" << title << "\n</summary>";
    builder.read_title(buffer);
    EXPECT_EQ(builder.result()->title, title);
}

TEST(NoteBuilder, Descriptions)
{
    flashback::markdown_note_builder builder{};

    std::stringstream buffer;
    buffer << "Some description to test" << "\n";
    buffer << "in multiple lines" << "\n";

    builder.read_description(buffer);
    EXPECT_EQ(builder.result()->description, buffer.str());
}

TEST(NoteBuilder, References)
{
    flashback::markdown_note_builder builder{};

    std::stringstream buffer;
    buffer << "* [sample1](url1)\n";
    buffer << "* [sample2](url2)\n";

    builder.read_references(buffer);
    EXPECT_EQ(builder.result()->position.size(), 2);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
