#pragma once

#include <cstdlib>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "session.h"

/**
 * @brief The Server class
 *
 */
class Server
{
public:
    Server(boost::asio::io_service &io_service, short port, std::shared_ptr<Database> db);

    /**
     * @brief start_accept
     *
     * Starts an asynchronous accept operation.
     *
     * @return void
     */
    void startAccept();

    /**
     * @brief handle_accept
     *
     * Handles completion of an asynchronous accept operation.
     *
     * @param new_session
     * @param error
     * @return void
     */
    void handleAccept(Session *new_session,
                       const boost::system::error_code &error);

private:
    boost::asio::io_service &ioService;
    tcp::acceptor acceptor;
    std::shared_ptr<Database> db;
};