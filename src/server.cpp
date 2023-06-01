#include "server.h"
#include "database.h"

Server::Server(boost::asio::io_service &io_service, short port)
    : ioService(io_service),
      acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
      db(std::make_shared<Database>())
{
    start_accept();
}

void Server::start_accept()
{
    Session *new_session = new Session(ioService, db);

    acceptor.async_accept(new_session->getSocket(),
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