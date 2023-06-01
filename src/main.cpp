#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "server.h"

void loadExampleDBData(std::shared_ptr<Database> db);

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cout << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        std::shared_ptr<Database> db = std::make_shared<Database>();
        loadExampleDBData(db);
        Server s(io_service, std::atoi(argv[1]), db);

        io_service.run();
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}

void loadExampleDBData(std::shared_ptr<Database> db)
{
    Database::Seats seats1 = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 1, 0, 0}};
    std::vector<std::string> available_seats1 = {
        "C3", "C4",
        "D3", "D4",
        "E3", "E4"};
    Database::Seats seats2 = {
        {0, 0, 1, 1},
        {0, 0, 1, 1},
        {1, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1}};
    std::vector<std::string> available_seats2 = {
        "A1", "A2",
        "B1", "B2",
        "C4"};

    db->add_show("m1", "t1", seats1);
    db->add_show("m1", "t2", seats2);
    db->add_show("m2", "t2", seats1);
}