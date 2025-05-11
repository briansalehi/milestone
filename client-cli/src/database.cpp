#include <milestone/database.hpp>

using namespace milestone;

database::database(boost::asio::ip::address address, uint16_t const port)
    : database_address{std::move(address)}
    , database_port{port}
{
}