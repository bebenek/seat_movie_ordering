#pragma once

#include <string>
#include <vector>


struct Database {
    Database() : movies({"The Shawshank Redemption", "The Godfather", "The Dark Knight"}) {};
    bool add_movie(std::string movie);
    bool remove_movie(std::string movie);
    const std::vector<std::string>& get_movies() const;
private:
    std::vector<std::string> movies;

};
