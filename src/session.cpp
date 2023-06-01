#include "session.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/algorithm/string/predicate.hpp>

Session::Session(boost::asio::io_service &io_service, std::shared_ptr<Database> db)
    : socket(io_service),
      service(db)
{
}

tcp::socket &Session::getSocket()
{
    return socket;
}

void Session::start()
{
    socket.async_read_some(boost::asio::buffer(dataStr, max_length),
                           boost::bind(&Session::handleRead, this,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred));
}

void Session::handleRead(const boost::system::error_code &error,
                          size_t bytes_transferred)
{
    if (error)
    {
        delete this;
        return;
    }
    std::string message(dataStr, bytes_transferred);
    if (boost::starts_with(message, "exit"))
    {
        delete this;
        return;
    }
    const auto &output = service.processMessage(message);

    boost::asio::async_write(socket,
                                boost::asio::buffer(output.c_str(), output.size()),
                                boost::bind(&Session::handleWrite, this,
                                            boost::asio::placeholders::error));
}

void Session::handleWrite(const boost::system::error_code &error)
{
    if (error)
    {
        delete this;
        return;
    }
    socket.async_read_some(boost::asio::buffer(dataStr, max_length),
                            boost::bind(&Session::handleRead, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}