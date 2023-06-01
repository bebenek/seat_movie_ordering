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
                           boost::bind(&Session::handle_read, this,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred));
}

void Session::handle_read(const boost::system::error_code &error,
                          size_t bytes_transferred)
{
    if (!error)
    {
        std::string message(dataStr, bytes_transferred);
        if (boost::starts_with(message, "exit"))
        {
            delete this;
            return;
        }
        const auto &output = service.process_message(message);

        boost::asio::async_write(socket,
                                 boost::asio::buffer(output.c_str(), output.size()),
                                 boost::bind(&Session::handle_write, this,
                                             boost::asio::placeholders::error));
    }
    else
    {
        delete this;
    }
}

void Session::handle_write(const boost::system::error_code &error)
{
    if (!error)
    {
        socket.async_read_some(boost::asio::buffer(dataStr, max_length),
                               boost::bind(&Session::handle_read, this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        delete this;
    }
}