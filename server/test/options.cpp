#include <flashback/options.hpp>
#include <gtest/gtest.h>
#include <array>

TEST(Server, Options)
{
    flashback::options options{};
    int const argc{8};
    std::array<char const*, 8> argv{};
    argv.at(0) = "server";
    argv.at(1) = "-a";
    argv.at(2) = "127.0.0.1";
    argv.at(3) = "-p";
    argv.at(4) = "8080";
    argv.at(5) = "-6";
    argv.at(6) = "-l";
    argv.at(7) = "/tmp/flashback.log";

    options.parse(argc, argv.data());

    EXPECT_EQ(options.address, "127.0.0.1");
    EXPECT_EQ(options.port, 8080);
    EXPECT_TRUE(options.ipv6_only);
    EXPECT_EQ(options.logfile, std::filesystem::path{"/tmp/flashback.log"});
}
