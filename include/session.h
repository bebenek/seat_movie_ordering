#pragma once

#include <memory>
#include <boost/asio.hpp>
#include "service.h"

struct Database;
using boost::asio::ip::tcp;

/**
 * @brief A session is a connection between a client and the server.
 */
class Session
{
public:
    Session(boost::asio::io_service &io_service, std::shared_ptr<Database> db);

    /**
     * @brief Get the socket object
     *
     * @return tcp::socket&
     */
    tcp::socket &getSocket();

    /**
     * @brief Start the session by reading from the socket.
     *
     * @return void
     */
    void start();

    /**
     * @brief Handle a read from the socket.
     *
     *
     * @param error
     * @param bytes_transferred
     * @return void
     */
    void handleRead(const boost::system::error_code &error,
                     size_t bytes_transferred);

    /**
     * @brief Handle a write to the socket.
     *
     * @param error
     * @return void
     */
    void handleWrite(const boost::system::error_code &error);

private:
    Service service;
    tcp::socket socket;
    enum
    {
        max_length = 1024
    };
    char dataStr[max_length];
};