#include <flashback/markdown_book_builder.hpp>
#include <flashback/book.hpp>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

TEST(ResourceBuilder, Construction)
{
    std::filesystem::path source_path{"/tmp/flashback.data"};
    flashback::markdown_book_builder builder{source_path};
    EXPECT_EQ(builder.result() == nullptr, false);

    builder.reset();
    EXPECT_EQ(builder.result() == nullptr, false);
}

TEST(ResourceBuilder, Title)
{
    std::filesystem::path source_path{"/tmp/flashback.data"};
    std::fstream source{source_path, std::ios::trunc | std::ios::out};

    ASSERT_EQ(source.is_open(), true);
    source << "# [Book Name](link to book)";
    source.close();

    try
    {
        flashback::markdown_book_builder builder{source_path};
        builder.read_title();

        EXPECT_EQ(builder.result()->title(), "Book Name");
    }
    catch (std::runtime_error const& exp)
    { }
}

TEST(ResourceBuilder, Chapter)
{
    std::filesystem::path source_path{"/tmp/flashback.data"};
    std::fstream source{source_path, std::ios::trunc | std::ios::out};

    source << "# [Book Name](link to book)" << "\n";
    source << "## Chapter 1/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 1 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 1" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 1](link)" << "\n";
    source << "## Chapter 2/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 2 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 2" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 2](link)" << "\n";
    source << "## Chapter 3/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 3 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 3" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 3](link)" << "\n";

    ASSERT_EQ(source.is_open(), true);

    try
    {
        flashback::markdown_book_builder builder{source_path};
        builder.read_title();
        builder.read_chapters();

        EXPECT_EQ(builder.result()->notes().size(), 3);
        EXPECT_EQ(dynamic_cast<flashback::book*>(builder.result().get())->chapters(), 3);
    }
    catch (std::runtime_error const& exp)
    { }
}

TEST(ResourceBuilder, NoteTitle)
{
    std::filesystem::path source_path{"/tmp/flashback.data"};
    std::fstream source{source_path, std::ios::trunc | std::ios::out};

    source << "# [Book Name](link to book)" << "\n";
    source << "## Chapter 1/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 1 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 1" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 1](link)" << "\n";
    source << "## Chapter 2/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 2 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 2" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 2](link)" << "\n";
    source << "## Chapter 3/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 3 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 3" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 3](link)" << "\n";

    try
    {
        flashback::markdown_book_builder builder{source_path};
        builder.read_title();
        builder.read_chapters();

        EXPECT_EQ(builder.result()->notes().at(0)->title(), "Sample 1 of 3");
        EXPECT_EQ(builder.result()->notes().at(1)->title(), "Sample 2 of 3");
        EXPECT_EQ(builder.result()->notes().at(2)->title(), "Sample 3 of 3");
    }
    catch (std::runtime_error const& exp)
    { }
}

TEST(ResourceBuilder, NoteDescription)
{
    std::filesystem::path source_path{"/tmp/flashback.data"};
    std::fstream source{source_path, std::ios::trunc | std::ios::out};

    source << "# [Book Name](link to book)" << "\n";
    source << "## Chapter 1/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 1 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 1" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 1](link)" << "\n";
    source << "## Chapter 2/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 2 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 2" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 2](link)" << "\n";
    source << "## Chapter 3/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 3 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 3" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 3](link)" << "\n";

    try
    {
        flashback::markdown_book_builder builder{source_path};
        builder.read_title();
        builder.read_chapters();

        EXPECT_EQ(builder.result()->notes().at(0)->description(), "Quote 1");
        EXPECT_EQ(builder.result()->notes().at(1)->description(), "Quote 2");
        EXPECT_EQ(builder.result()->notes().at(2)->description(), "Quote 3");
    }
    catch (std::runtime_error const& exp)
    { }
}

TEST(ResourceBuilder, NotePosition)
{
    std::filesystem::path source_path{"/tmp/flashback.data"};
    std::fstream source{source_path, std::ios::trunc | std::ios::out};

    source << "# [Book Name](link to book)" << "\n";
    source << "## Chapter 1/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 1 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 1" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 1](link)" << "\n";
    source << "## Chapter 2/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 2 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 2" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 2](link)" << "\n";
    source << "## Chapter 3/3" << "\n";
    source << "<details>" << "\n";
    source << "<summary>Sample 3 of 3</summary>" << "\n";
    source << "\n";
    source << "Quote 3" << "\n";
    source << "</details>" << "\n";
    source << "* [reference 3](link)" << "\n";

    try
    {
        flashback::markdown_book_builder builder{source_path};
        builder.read_title();
        builder.read_chapters();

        EXPECT_EQ(builder.result()->notes().at(0)->position().empty(), true);
        EXPECT_EQ(builder.result()->notes().at(1)->position().empty(), true);
        EXPECT_EQ(builder.result()->notes().at(2)->position().empty(), true);
    }
    catch (std::runtime_error const& exp)
    { }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
