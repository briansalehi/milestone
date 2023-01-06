#include <flashback/markdown_resource_builder.hpp>
#include <flashback/book.hpp>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

TEST(ResourceBuilder, Construction)
{
    flashback::markdown_resource_builder builder{};
    EXPECT_EQ(builder.result() == nullptr, false);

    builder.reset();
    EXPECT_EQ(builder.result() == nullptr, false);
}

TEST(ResourceBuilder, Title)
{
    flashback::markdown_resource_builder builder{};
    std::stringstream buffer{"# [Book Name](link to book)"};

    try
    {
        builder.read_title(buffer);
    }
    catch (std::runtime_error const& exp)
    { }

    EXPECT_EQ(builder.result()->title(), "Book Name");
}

TEST(ResourceBuilder, Chapter)
{
    flashback::markdown_resource_builder builder{};
    std::stringstream buffer;

    buffer << "# [Book Name](link to book)" << "\n";
    buffer << "## Chapter 1/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 1 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 1" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 1](link)" << "\n";
    buffer << "## Chapter 2/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 2 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 2" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 2](link)" << "\n";
    buffer << "## Chapter 3/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 3 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 3" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 3](link)" << "\n";

    try
    {
        builder.read_title(buffer);
        builder.read_chapters(buffer);
    }
    catch (std::runtime_error const& exp)
    { }

    EXPECT_EQ(builder.result()->notes().size(), 3);
    EXPECT_EQ(dynamic_cast<flashback::book*>(builder.result().get())->chapters(), 3);
}

TEST(ResourceBuilder, NoteTitle)
{
    flashback::markdown_resource_builder builder{};
    std::stringstream buffer;

    buffer << "# [Book Name](link to book)" << "\n";
    buffer << "## Chapter 1/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 1 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 1" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 1](link)" << "\n";
    buffer << "## Chapter 2/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 2 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 2" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 2](link)" << "\n";
    buffer << "## Chapter 3/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 3 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 3" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 3](link)" << "\n";

    try
    {
        builder.read_title(buffer);
        builder.read_chapters(buffer);
    }
    catch (std::runtime_error const& exp)
    { }

    EXPECT_EQ(builder.result()->notes().at(0)->title(), "Sample 1 of 3");
    EXPECT_EQ(builder.result()->notes().at(1)->title(), "Sample 2 of 3");
    EXPECT_EQ(builder.result()->notes().at(2)->title(), "Sample 3 of 3");
}

TEST(ResourceBuilder, NoteDescription)
{
    flashback::markdown_resource_builder builder{};
    std::stringstream buffer;

    buffer << "# [Book Name](link to book)" << "\n";
    buffer << "## Chapter 1/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 1 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 1" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 1](link)" << "\n";
    buffer << "## Chapter 2/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 2 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 2" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 2](link)" << "\n";
    buffer << "## Chapter 3/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 3 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 3" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 3](link)" << "\n";

    try
    {
        builder.read_title(buffer);
        builder.read_chapters(buffer);
    }
    catch (std::runtime_error const& exp)
    { }

    EXPECT_EQ(builder.result()->notes().at(0)->description(), "Quote 1");
    EXPECT_EQ(builder.result()->notes().at(1)->description(), "Quote 2");
    EXPECT_EQ(builder.result()->notes().at(2)->description(), "Quote 3");
}

TEST(ResourceBuilder, NotePosition)
{
    flashback::markdown_resource_builder builder{};
    std::stringstream buffer;

    buffer << "# [Book Name](link to book)" << "\n";
    buffer << "## Chapter 1/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 1 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 1" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 1](link)" << "\n";
    buffer << "## Chapter 2/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 2 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 2" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 2](link)" << "\n";
    buffer << "## Chapter 3/3" << "\n";
    buffer << "<details>" << "\n";
    buffer << "<summary>Sample 3 of 3</summary>" << "\n";
    buffer << "\n";
    buffer << "Quote 3" << "\n";
    buffer << "</details>" << "\n";
    buffer << "* [reference 3](link)" << "\n";

    try
    {
        builder.read_title(buffer);
        builder.read_chapters(buffer);
    }
    catch (std::runtime_error const& exp)
    { }

    EXPECT_EQ(builder.result()->notes().at(0)->position().empty(), true);
    EXPECT_EQ(builder.result()->notes().at(1)->position().empty(), true);
    EXPECT_EQ(builder.result()->notes().at(2)->position().empty(), true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
