#pragma once

#include <cstdlib>
#include <iostream>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "session.h"

class Server
{
public:
    Server(boost::asio::io_service &io_service, short port);

    void start_accept();

    void handle_accept(Session *new_session,
                       const boost::system::error_code &error);

private:
    boost::asio::io_service &io_service_;
    tcp::acceptor acceptor_;
    std::shared_ptr<Database> db_;
};