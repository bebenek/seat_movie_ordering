#pragma once

#include <string>

class RequestHandler
{
public:
    RequestHandler(/* args */);
    ~RequestHandler();

    std::string handle_request(std::string request);
};