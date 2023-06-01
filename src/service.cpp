
#include "service.h"

Service::Service(std::shared_ptr<Database> db) : db(db), requestHandler()
{
}

std::string Service::process_message(const std::string &message)
{
    const auto &req = requestHandler.handle_request(message);
    if (!req.success)
    {
        return responseGenerator.generateJsonErrorResponse("Parsing error");
    }
    if (req.seat && req.theater && req.movie)
    {
        bool reserved_succesfully = db->reserve_seat(*req.movie, *req.theater, *req.seat);
        const auto &seats = db->get_seats_by_movie_and_theater(*req.movie, *req.theater);
        if (!seats)
        {
            return responseGenerator.generateJsonErrorResponse("Movie or theater not found");
        }
        return responseGenerator.generateJsonSeatsResponse(*req.movie, *req.theater, *seats, reserved_succesfully);
    }
    else if (req.theater && req.movie)
    {
        const auto &seats = db->get_seats_by_movie_and_theater(*req.movie, *req.theater);
        if (!seats)
        {
            return responseGenerator.generateJsonErrorResponse("Movie or theater not found");
        }
        return responseGenerator.generateJsonSeatsResponse(*req.movie, *req.theater, *seats);
    }
    else if (req.movie)
    {
        const auto &theaters = db->get_theaters_by_movie(*req.movie);
        if (!theaters)
        {
            return responseGenerator.generateJsonErrorResponse("Movie not found");
        }
        return responseGenerator.generateJsonTheatersResponse(*req.movie, *theaters);
    }
    else if (!req.movie && !req.theater && !req.seat)
    {
        const auto &movies = db->get_movies();
        return responseGenerator.generateJsonMoviesResponse(movies);
    }
    return responseGenerator.generateJsonErrorResponse("Unknown error");
}
