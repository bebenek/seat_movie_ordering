#include "request_handler.h"
#include "rapidjson/document.h"
#include "database.h"


using namespace rapidjson;

RequestHandler::Request RequestHandler::handle_request(std::string request) const{
     Document d;
    ParseResult ok = d.Parse(request.c_str());

    if (ok && d.HasMember("movie")) {
        return {"Hello " + std::string(d["movie"].GetString()) + "!", boost::none, boost::none};
    }
    return {boost::none, boost::none, boost::none};
}