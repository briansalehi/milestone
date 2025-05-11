#include <milestone/client.hpp>
#include <print>
#include <iostream>
#include <string>
#include <format>

using namespace milestone;

static constexpr char const* request_format{
    "GET {0} HTTP/1.1{1}"
    "Host: {2}:{3}{1}"
    "Accept: application/json{1}{1}"
};

client::client(options const& opts)
    : m_options{opts}
    , m_screen{}
    , m_context{}
    , m_socket{m_context}
{
    connect();
}

client::~client()
{
    disconnect();
}

void client::connect() &
{
    boost::asio::ip::tcp::resolver resolver{m_context};
    boost::asio::ip::tcp::resolver::iterator const endpoints{ resolver.resolve(m_options.server_address, m_options.server_port)};
    boost::asio::connect(m_socket, endpoints);
}

void client::disconnect() &
{
    if (m_socket.is_open())
    {
        m_socket.close();
    }
}

void client::make_request(std::string const& path) &
{
    boost::asio::ip::tcp::endpoint const server{m_socket.remote_endpoint()};
    std::string request_header{std::format(request_format, path, "\r\n", server.address().to_string(), server.port())};
    boost::system::error_code code;

    std::size_t sent_bytes = boost::asio::write(m_socket, boost::asio::buffer(request_header), code);
    if (code)
    {
        std::println(std::cerr, "write error: {}", code.message());
        throw boost::system::system_error(code);
    }

    boost::asio::streambuf buffer;
    boost::asio::read_until(m_socket, buffer, "\r\n\r\n", code);
    if (code)
    {
        std::println(std::cerr, "read error: {}", code.message());
        throw boost::system::system_error(code);
    }

    std::istream stream(&buffer);
    std::string line{};
    std::size_t content_length{};

    while (std::getline(stream, line) && line != "\r")
    {
        if (line.contains("Content-Length"))
        {
            content_length = std::stoul(line.substr(15));
        }
    }

    std::size_t const body_size = content_length - buffer.size();
    std::size_t bytes_read = boost::asio::read(m_socket, buffer, boost::asio::transfer_exactly(body_size), code);
    if (code)
    {
        std::println(std::cerr, "read error: {}", code.message());
        throw boost::system::system_error(code);
    }

    std::string const body{std::istreambuf_iterator<char>(&buffer), {}};
    m_screen.print(0, 0, body);
}