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
    tcp::socket &getSocket();

    void start();

    void handle_read(const boost::system::error_code &error,
                     size_t bytes_transferred);
    void handle_write(const boost::system::error_code &error);

private:
    Service service;
    tcp::socket socket;
    enum
    {
        max_length = 1024
    };
    char dataStr[max_length];
};