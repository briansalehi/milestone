#include <flashback/flashcard.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>

TEST(Common, ValidTitleParsing)
{
    std::stringstream buffer;
    buffer << "<details>\n" << "<summary>Title</summary>\n\n";
    //buffer << "> First Line\n" << "> Second Line\n" << ">\n";
    buffer << "</details>\n";

    flashback::flashcard card(buffer);
    std::string expected{"Title"};
    std::string output{card.title};

    ASSERT_EQ(expected, output);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
