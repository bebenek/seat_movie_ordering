#pragma once

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <boost/optional.hpp>

/**
 * @brief Database class
 */
struct Database
{
    using Seats = int[5][4];
    using DatabaseType = std::map<std::string, std::map<std::string, Seats>>;

    Database() = default;

    /**
     * @brief Add a show to the database
     * @param movie Movie name
     * @param theater Theater name
     * @param seats Seats
     * @return true if the show was added, false otherwise
     */
    bool add_show(std::string movie, std::string theater, Seats seats);

    /**
     * @brief Get all movies
     * @return A vector of movies
     */
    std::vector<std::string> get_movies();

    /**
     * @brief Get all theaters for a movie
     * @param movie Movie name
     * @return A vector of theaters or boost::none if the movie does not exist
     */
    boost::optional<std::vector<std::string>> get_theaters_by_movie(std::string movie);

    /**
     * @brief Get all seats for a movie and theater
     * @param movie Movie name
     * @param theater Theater name
     * @return A vector of seats or boost::none if the movie or theater does not exist
     */
    boost::optional<std::vector<std::string>> get_seats_by_movie_and_theater(std::string movie, std::string theater);

    /**
     * @brief Reserve a seat for a movie and theater
     * @param movie Movie name
     * @param theater Theater name
     * @param seat Seat
     * @return true if the seat was reserved, false otherwise
     */
    bool reserve_seat(std::string movie, std::string theater, std::string seat);

private:
    DatabaseType database;
    std::mutex mutex;
};
