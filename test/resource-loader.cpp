#include <resource-loader.hpp>
#include <gtest/gtest.hpp>

#include <fstream>
#include <filesystem>

TEST(ResourceLoaderTest, LoaderTest)
{
    std::filesystem::path entities_path{"/tmp/"};
    std::ofstream context(entities_path / "book.md", std::ios::trunc | std::ios::out);
    context << "# Header\n" << "## Chapter 1/10\n" << "Chapter 2/10\n";
    context.close();

    resource_loader library(entities_path);
    EXPECT_EQ(library.entities_path(), entities_path);
    EXPECT_EQ(library.resources().empty(), true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
