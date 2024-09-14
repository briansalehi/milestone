#include <gtest/gtest.h>
#include <flashback/flashback.hpp>
#include <sstream>
#include <string>

TEST(Flashback, Database)
{
    flashback::database database{"postgresql://flashback@localhost/flashback"};
    ASSERT_EQ(database.is_connected(), true);

    constexpr std::size_t total_tokens{3};

    std::stringstream buffer{database.address()};;
    std::string token{};
    std::string user{};
    std::string dbname{};
    std::string host{};

    while (std::getline(buffer, token, ' '))
    {
        std::string::size_type middle{token.find("=")};
        std::string key{token.substr(0, middle)};
        std::string value{token.substr(middle + 1, token.size())};

        if (key == "user")
        {
            user = value;
        }
        else if (key == "dbname")
        {
            dbname = value;
        }
        else if (key == "host")
        {
            host = value;
        }
    }

    EXPECT_EQ(user, "flashback");
    EXPECT_EQ(host, "localhost");
    EXPECT_EQ(dbname, "flashback");
}
