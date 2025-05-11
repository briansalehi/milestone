#pragma once

#include <string>
#include <boost/asio.hpp>

namespace milestone
{
class server
{
public:
    explicit server(boost::asio::ip::address const& address, boost::asio::ip::port_type port);
    [[nodiscard]] std::string handle_request(std::string const& request) const&;
    void handle_client(boost::asio::ip::tcp::socket&& client) &;
    void listen() &;
private:
    boost::asio::io_context m_context;
    boost::asio::ip::tcp::endpoint m_endpoint;
    boost::asio::ip::tcp::acceptor m_acceptor;
};
} // milestone