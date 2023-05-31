#pragma once

#include <string>
#include <vector>


struct Database {
    bool add_movie(std::string movie);
    bool remove_movie(std::string movie);
    const std::vector<std::string>& get_movies() const;
private:
    std::vector<std::string> movies;

};