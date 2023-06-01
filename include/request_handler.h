#pragma once

#include <string>
#include <memory>
#include <boost/optional.hpp>

struct Database;

/**
 * @brief This class is responsible for handling the requests from the client.
 */
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

    /**
     * @brief This function handles the request from the client.
     *
     * Translates json to a RequestHandler::Request object.
     * boost::none if something missing or invalid.
     *
     * @param request The request from the client.
     * @return RequestHandler::Request The request from the client.
     */
    Request handle_request(std::string request) const;
};