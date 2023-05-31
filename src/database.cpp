#include "database.h"

bool Database::add_movie(std::string movie) {
    movies.push_back(movie);
    return true;
}

bool Database::remove_movie(std::string movie) {
    for (auto it = movies.begin(); it != movies.end(); ++it) {
        if (*it == movie) {
            movies.erase(it);
            return true;
        }
    }
    return false;
}

const std::vector<std::string>& Database::get_movies() const {
    return movies;
}
