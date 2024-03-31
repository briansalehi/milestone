#include <flashback/flashcard.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>

TEST(Common, ValidateParsing)
{
    std::stringstream buffer;
    buffer << "<details>\n"
        << "<summary>Title</summary>\n\n"
        << "> **Description**\n>\n"
        << "> First Line\n" << "> Second Line\n" << ">\n"
        << "> ---\n"
        << "> **Resources**\n"
        << "> - First Resource\n" << "> - Second Resource\n"
        << "> ---\n"
        << "> **References**\n"
        << "> - First Reference\n" << "> - Second Reference\n"
        << "> ---\n"
        << "</details>\n";

    flashback::flashcard card(buffer);
    std::string expected_title{"Title"};
    std::string output_title{card.title};
    std::string expected_body{"First Line\nSecond Line\n\n"};
    std::string output_body{card.body};
    std::vector<std::string> expected_resources{{"First Resource"}, {"Second Resource"}};
    std::vector<std::string> output_resources{card.resources};
    std::vector<std::string> expected_references{{"First Reference"}, {"Second Reference"}};
    std::vector<std::string> output_references{card.references};

    ASSERT_EQ(expected_title, output_title);
    ASSERT_EQ(expected_body, output_body);
    ASSERT_EQ(expected_resources, output_resources);
    ASSERT_EQ(expected_references, output_references);
}

TEST(Common, TolerateBrokenBody)
{
    std::stringstream buffer;
    buffer << "<details>\n"
        << "<summary>Title</summary>\n\n"
        << "> **Description**\n>\n"
        << "> First Line\n" << "Second Line\n" << ">\n"
        << "> ---\n"
        << "> **Resources**\n"
        << "> - First Resource\n" << "> - Second Resource\n"
        << "> ---\n"
        << "> **References**\n"
        << "> - First Reference\n" << "> - Second Reference\n"
        << "> ---\n"
        << "</details>\n";

    flashback::flashcard card(buffer);
    std::string expected_body{"First Line\nSecond Line\n\n"};
    std::string output_body{card.body};

    ASSERT_EQ(expected_body, output_body);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
