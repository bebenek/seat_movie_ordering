#include "session.h"
#include <boost/bind.hpp>

Session::Session(boost::asio::io_service &io_service, std::shared_ptr<Database> db)
    : socket_(io_service),
        request_handler_(),
        db_(db)
{
}

tcp::socket &Session::socket()
{
    return socket_;
}

void Session::start()
{
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
                            boost::bind(&Session::handle_read, this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void Session::handle_read(const boost::system::error_code &error,
                          size_t bytes_transferred)
{
    if (!error)
    {
        const auto& output = request_handler_.handle_request(std::string(data_, bytes_transferred));

        boost::asio::async_write(socket_,
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
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                boost::bind(&Session::handle_read, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
        delete this;
    }
}