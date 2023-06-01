#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "server.h"

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

        using namespace std; // For atoi.
        Server s(io_service, atoi(argv[1]));

        io_service.run();
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}
