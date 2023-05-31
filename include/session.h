#pragma once

#include <memory>
#include <boost/asio.hpp>
#include "service.h"

struct Database;
using boost::asio::ip::tcp;
class Session
{
public:
    Session(boost::asio::io_service &io_service, std::shared_ptr<Database> db);
    tcp::socket &socket();

    void start();

    void handle_read(const boost::system::error_code &error,
                     size_t bytes_transferred);
    void handle_write(const boost::system::error_code &error);

private:
    Service service_;
    tcp::socket socket_;
    enum
    {
        max_length = 1024
    };
    char data_[max_length];
};