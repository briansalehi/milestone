#include <flashback/markdown_note_builder.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <string>

using namespace std::literals::string_literals;

TEST(NoteBuilder, Construction)
{
    std::ifstream buffer{"/tmp/flashback.data", std::ios::in};
    ASSERT_EQ(buffer.is_open(), true);

    flashback::markdown_note_builder builder{buffer};

    EXPECT_EQ(builder.result() == nullptr, false);
    builder.reset();

    EXPECT_EQ(builder.result() == nullptr, false);
}

TEST(NoteBuilder, SingleLineTitle)
{
    std::ofstream source{"/tmp/flashback.data", std::ios::out | std::ios::trunc};

    ASSERT_EQ(source.is_open(), true);
    source << "<summary>Single Line Title</summary>";
    source.close();

    std::ifstream buffer{"/tmp/flashback.data", std::ios::in};
    ASSERT_EQ(buffer.is_open(), true);

    flashback::markdown_note_builder builder{buffer};
    builder.read_title();
    buffer.close();

    EXPECT_EQ(builder.result()->title(), "Single Line Title"s);
}

TEST(NoteBuilder, MultiLineTitle)
{
    std::ofstream source{"/tmp/flashback.data", std::ios::out | std::ios::trunc};
    ASSERT_EQ(source.is_open(), true);
    source << "<summary>";
    source << "Multi Line Title";
    source << "</summary>";
    source.close();

    std::ifstream buffer{"/tmp/flashback.data", std::ios::in};
    ASSERT_EQ(buffer.is_open(), true);

    flashback::markdown_note_builder builder{buffer};
    builder.read_title();

    EXPECT_EQ(builder.result()->title(), "Multi Line Title");
    buffer.close();
}

TEST(NoteBuilder, Descriptions)
{
    std::string content{};
    content.append("Some description to test");
    content.append("in multiple lines");

    std::ofstream source{"/tmp/flashback.data", std::ios::out | std::ios::trunc};
    ASSERT_EQ(source.is_open(), true);
    source << content;
    source.close();

    std::ifstream buffer{"/tmp/flashback.data", std::ios::in};
    ASSERT_EQ(buffer.is_open(), true);

    flashback::markdown_note_builder builder{buffer};
    builder.read_description();
    buffer.close();

    EXPECT_EQ(builder.result()->description(), content);
}

TEST(NoteBuilder, Position)
{
    std::ofstream source{"/tmp/flashback.data", std::ios::out | std::ios::trunc};
    ASSERT_EQ(source.is_open(), true);
    source.close();

    std::ifstream buffer{"/tmp/flashback.data", std::ios::in};
    ASSERT_EQ(buffer.is_open(), true);

    flashback::markdown_note_builder builder{buffer};
    builder.read_references();
    buffer.close();

    EXPECT_EQ(builder.result()->position().empty(), true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
