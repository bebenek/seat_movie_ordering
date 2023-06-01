#include "database.h"

bool Database::add_show(std::string movie, std::string theater, Seats seats)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto &theaters = database[movie];
    auto &seats_by_theater = theaters[theater];
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            seats_by_theater[i][j] = seats[i][j];
        }
    }
    return true;
}

std::vector<std::string> Database::get_movies()
{
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<std::string> movies;
    for (const auto &movie : database)
    {
        movies.push_back(movie.first);
    }
    return movies;
}

boost::optional<std::vector<std::string>> Database::get_theaters_by_movie(std::string movie)
{
    std::lock_guard<std::mutex> lock(mutex);
    static std::vector<std::string> empty;
    auto it = database.find(movie);
    if (it == database.end())
    {
        return boost::none;
    }
    std::vector<std::string> theaters;
    for (const auto &theater : it->second)
    {
        theaters.push_back(theater.first);
    }
    return theaters;
}

boost::optional<std::vector<std::string>> Database::get_seats_by_movie_and_theater(std::string movie, std::string theater)
{
    std::lock_guard<std::mutex> lock(mutex);
    static std::vector<std::string> empty;
    auto it = database.find(movie);
    if (it == database.end())
    {
        return boost::none;
    }
    auto it2 = it->second.find(theater);
    if (it2 == it->second.end())
    {
        return boost::none;
    }
    std::vector<std::string> seats;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (it2->second[i][j] == 0)
            {
                seats.push_back(std::string(1, 'A' + i) + std::string(1, '1' + j));
            }
        }
    }
    return seats;
}

bool Database::reserve_seat(std::string movie, std::string theater, std::string seat)
{
    std::lock_guard<std::mutex> lock(mutex);
    auto it = database.find(movie);
    if (it == database.end())
    {
        return false;
    }
    auto it2 = it->second.find(theater);
    if (it2 == it->second.end())
    {
        return false;
    }
    auto &seats = it2->second;
    int row = seat[0] - 'A';
    int col = seat[1] - '1';
    if (row < 0 || row > 4 || col < 0 || col > 3)
    {
        return false;
    }
    if (seats[row][col] == 1)
    {
        return false;
    }
    seats[row][col] = 1;
    return true;
}