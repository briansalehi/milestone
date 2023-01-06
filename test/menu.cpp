#include <gtest/gtest.h>
#include <flashback/menu.hpp>

#include <string>

TEST(Menu, Construction)
{
    std::string section{"library"};
    flashback::menu menu{section};
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
