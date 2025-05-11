#pragma once

#include <cstdint>
#include <boost/asio.hpp>

namespace milestone
{
class database
{
public:
    explicit database(boost::asio::ip::address address, uint16_t port = 5432u);
private:
    boost::asio::ip::address database_address;
    uint16_t database_port;
};
} // milestone