#pragma once

#include <string>
#include <vector>
#include <boost/optional.hpp>

/**
 * @brief This class is responsible for generating the JSON responses.
 */
class ResponseGenerator
{
public:
    /**
     * @brief Generates a JSON response with the movies.
     *
     * @param movies The movies to be included in the response.
     * @return std::string The JSON response.
     */
    std::string generateJsonMoviesResponse(const std::vector<std::string> &movies) const;

    /**
     * @brief Generates a JSON response with the theaters.
     *
     * @param movie The movie to be included in the response.
     * @param theaters The theaters to be included in the response.
     * @return std::string The JSON response.
     */
    std::string generateJsonTheatersResponse(std::string movie, const std::vector<std::string> &theaters) const;

    /**
     * @brief Generates a JSON response with the seats.
     *
     * reserved_succesfully is optional because it is only used when the request is to reserve a seat.
     *
     * @param movie The movie to be included in the response.
     * @param theater The theater to be included in the response.
     * @param seats The seats to be included in the response.
     * @param reserved_successfully Whether the seats were reserved successfully or not.
     * @return std::string The JSON response.
     */
    std::string generateJsonSeatsResponse(std::string movie, std::string theater, const std::vector<std::string> &seats, boost::optional<bool> reserved_successfully = boost::none) const;

    /**
     * @brief Generates a JSON response with an error message.
     *
     * @param errorMessage The error message to be included in the response.
     * @return std::string The JSON response.
     */
    std::string generateJsonErrorResponse(std::string errorMessage) const;
};