#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "server.h"
#include "file_parser.h"
#include "database.h"


int main(int argc, char *argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cout << "Usage: movie_reser <port> <filename>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        std::shared_ptr<Database> db = std::make_shared<Database>();
        if (!FileParser::parseFile(argv[2], db))
        {
            std::cout << "Could not parse the file: " << argv[2] << std::endl;
            return 1;

        }
        Server s(io_service, std::atoi(argv[1]), db);

        io_service.run();
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}
