#include <iostream>
#include <print>
#include <milestone/server.hpp>

using namespace milestone;

server::server(boost::asio::ip::address const& address, boost::asio::ip::port_type const port)
    : m_context{}
    , m_endpoint{address, port}
    , m_acceptor{m_context, m_endpoint}
{
}

std::string server::handle_request(std::string const& request) const&
{
    std::ostringstream stream;

    if (request.find("GET /resources") == 0)
    {
        stream << "HTTP/1.1 200 OK\r\n";
        stream << "Content-Type: application/json\r\n\r\n";
        stream << "";
    }

    return stream.str();
}

void server::handle_client(boost::asio::ip::tcp::socket&& client) &
{
}

void server::listen() &
{
    std::println(std::clog, "Server is listening on {}:{}", m_endpoint.address().to_string(), m_endpoint.port());
}