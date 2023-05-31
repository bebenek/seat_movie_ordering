#pragma once

#include <string>
#include <memory>
#include <boost/optional.hpp>

struct Database;
class RequestHandler
{
public:
    RequestHandler() = default;
    ~RequestHandler() = default;

    struct Request {
        Request(boost::optional<std::string> movie, boost::optional<std::string> theater, boost::optional<std::string> seat)
            : movie(movie), theater(theater), seat(seat) {}
        boost::optional<std::string> movie;
        boost::optional<std::string> theater;
        boost::optional<std::string> seat;
    };

    Request handle_request(std::string request) const;
};