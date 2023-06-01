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
    bool addShow(const std::string& movie, const std::string& theater, const Seats& seats);

    /**
     * @brief Get all movies
     * @return A vector of movies
     */
    std::vector<std::string> getMovies();

    /**
     * @brief Get all theaters for a movie
     * @param movie Movie name
     * @return A vector of theaters or boost::none if the movie does not exist
     */
    boost::optional<std::vector<std::string>> getTheatersByMovie(const std::string& movie);

    /**
     * @brief Get all seats for a movie and theater
     * @param movie Movie name
     * @param theater Theater name
     * @return A vector of seats or boost::none if the movie or theater does not exist
     */
    boost::optional<std::vector<std::string>> getSeatsByMovieAndTheater(const std::string& movie, const std::string& theater);

    /**
     * @brief Reserve a seat for a movie and theater
     * @param movie Movie name
     * @param theater Theater name
     * @param seat Seat
     * @return true if the seat was reserved, false otherwise
     */
    bool reserveSeat(const std::string& movie, const std::string& theater, const std::string& seat);

private:
    DatabaseType database;
    std::mutex mutex;
};
