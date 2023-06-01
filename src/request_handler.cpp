#include "request_handler.h"
#include "rapidjson/document.h"
#include "database.h"

using namespace rapidjson;

RequestHandler::Request RequestHandler::handle_request(std::string request) const
{
    Document d;
    ParseResult ok = d.Parse(request.c_str());
    if (!ok)
    {
        return {boost::none, boost::none, boost::none};
    }
    boost::optional<std::string> movie = boost::none;
    boost::optional<std::string> theater = boost::none;
    boost::optional<std::string> seat = boost::none;

    auto it = d.FindMember("movie");
    if (it != d.MemberEnd()) {
        auto& v = it->value;
        if (v.IsString()) {
            movie = v.GetString();
        } else {
            return {boost::none, boost::none, boost::none};
        }
    } else {
        return {movie, theater, seat};
    }

    it = d.FindMember("theater");
    if (it != d.MemberEnd()) {
        auto& v = it->value;
        if (v.IsString()) {
            theater = v.GetString();
        } else {
            return {boost::none, boost::none, boost::none};
        }
    } else {
        return {movie, theater, seat};
    }

    it = d.FindMember("seat");
    if (it != d.MemberEnd()) {
        auto& v = it->value;
        if (v.IsString()) {
            seat = v.GetString();
        } else {
            return {boost::none, boost::none, boost::none};
        }
    }

    return {movie, theater, seat};
}