#include "request_handler.h"
#include "rapidjson/document.h"


using namespace rapidjson;

RequestHandler::RequestHandler(/* args */)
{
}

RequestHandler::~RequestHandler()
{
}

std::string RequestHandler::handle_request(std::string request) {
     Document d;
    ParseResult ok = d.Parse(request.c_str());

    if (ok && d.HasMember("movie")) {
        return "Hello " + std::string(d["movie"].GetString()) + "!";
    }
    return "Hello World!";
}