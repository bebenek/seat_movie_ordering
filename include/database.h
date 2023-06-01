#pragma once

#include <string>
#include <vector>
#include <map>
#include <mutex>


struct Database {
    using Seats = int[5][4];
    using DatabaseType = std::map<std::string, std::map<std::string, Seats>>;
    Database() = default;
    bool add_show(std::string movie, std::string theater, Seats seats);
    std::vector<std::string> get_movies();
    std::vector<std::string> get_theaters_by_movie(std::string movie);
    std::vector<std::string> get_seats_by_movie_and_theater(std::string movie, std::string theater);
    bool reserve_seat(std::string movie, std::string theater, std::string seat);
private:
    DatabaseType database;
    std::mutex mutex;

};
