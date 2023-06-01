#pragma once

#include <string>
#include <vector>

class ResponseGenerator {
public:
    std::string generateJsonMoviesResponse(const std::vector<std::string>& movies) const;
    std::string generateJsonTheatersResponse(std::string movie, const std::vector<std::string>& theaters) const;
    std::string generateJsonSeatsResponse(std::string movie, std::string theater, const std::vector<std::string>& seats) const;
};