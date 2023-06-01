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

    struct Request
    {
        Request(boost::optional<std::string> movie, boost::optional<std::string> theater, boost::optional<std::string> seat, bool success = true)
            : movie(movie), theater(theater), seat(seat), success(success) {}
        boost::optional<std::string> movie;
        boost::optional<std::string> theater;
        boost::optional<std::string> seat;
        bool success;
    };

    Request handle_request(std::string request) const;
};