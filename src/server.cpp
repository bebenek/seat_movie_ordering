#include "server.h"
#include "database.h"

Server::Server(boost::asio::io_service &io_service, short port, std::shared_ptr<Database> db)
    : ioService(io_service),
      acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
      db(db)
{
    startAccept();
}

void Server::startAccept()
{
    Session *new_session = new Session(ioService, db);

    acceptor.async_accept(new_session->getSocket(),
                          boost::bind(&Server::handleAccept, this, new_session,
                                      boost::asio::placeholders::error));
}

void Server::handleAccept(Session *new_session,
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

    startAccept();
}