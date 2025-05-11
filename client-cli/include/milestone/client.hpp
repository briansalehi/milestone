#pragma once

#include <milestone/exceptions.hpp>
#include <milestone/options.hpp>
#include <milestone/screens.hpp>
#include <milestone/session.hpp>
#include <milestone/database.hpp>
#include <boost/asio.hpp>

namespace milestone
{
class client
{
public:
    explicit client(options const& opts);
    virtual ~client();
    void make_request(std::string const& path) &;
private:
    void connect() &;
    void disconnect() &;
private:
    options m_options;
    screens m_screen;
    boost::asio::io_context m_context;
    boost::asio::ip::tcp::socket m_socket;
};
} // milestone