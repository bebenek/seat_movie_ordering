#include "server.h"
#include "database.h"

Server::Server(boost::asio::io_service &io_service, short port)
    : io_service_(io_service),
      acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      db_(std::make_shared<Database>())
{
    start_accept();
}

void Server::start_accept()
{
    Session *new_session = new Session(io_service_, db_);

    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&Server::handle_accept, this, new_session,
                                       boost::asio::placeholders::error));
}

void Server::handle_accept(Session *new_session,
                           const boost::system::error_code &error)
{
    if (!error)
    {
        new_session->start();
    }
    else
    {
        delete new_session;
    }

    start_accept();
}