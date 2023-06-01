#pragma once

#include <string>
#include <vector>
#include <boost/optional.hpp>

class ResponseGenerator
{
public:
    std::string generateJsonMoviesResponse(const std::vector<std::string> &movies) const;
    std::string generateJsonTheatersResponse(std::string movie, const std::vector<std::string> &theaters) const;
    std::string generateJsonSeatsResponse(std::string movie, std::string theater, const std::vector<std::string> &seats, boost::optional<bool> reserved_succesfully = boost::none) const;
    std::string generateJsonErrorResponse(std::string errorMessage) const;
};