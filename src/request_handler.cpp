#include "request_handler.h"
#include "rapidjson/document.h"
#include "database.h"

using namespace rapidjson;

RequestHandler::Request RequestHandler::handleRequest(const std::string& request) const
{
    Document d;
    ParseResult ok = d.Parse(request.c_str());
    static const RequestHandler::Request invalid_request = {boost::none, boost::none, boost::none, false};
    if (!ok)
    {
        return invalid_request;
    }
    boost::optional<std::string> movie = boost::none;
    boost::optional<std::string> theater = boost::none;
    boost::optional<std::vector<std::string>> seats = boost::none;

    // parse movie
    auto it = d.FindMember("movie");
    if (it == d.MemberEnd()) // no movie
        return {movie, theater, seats};
    auto &v = it->value;
    if (!v.IsString())
    return invalid_request;
        movie = v.GetString();

    // parse theater
    it = d.FindMember("theater");
    if (it == d.MemberEnd()) // no theater
        return {movie, theater, seats};
    v = it->value;
    if (!v.IsString())
        return invalid_request;
    theater = v.GetString();

    // parse seats
    it = d.FindMember("seats");
    if (it == d.MemberEnd()) // no seats
        return {movie, theater, seats};
    v = it->value;
    if (!v.IsArray())
        return invalid_request;
    seats = std::vector<std::string>();
    for (auto& seat : v.GetArray())
    {
        if (!seat.IsString())
            return invalid_request;
        seats->emplace_back(seat.GetString());
    }


    return {movie, theater, seats};
}