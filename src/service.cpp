
#include "service.h"

Service::Service(std::shared_ptr<Database> db) : db(db), requestHandler()
{
}

std::string Service::processMessage(const std::string &message)
{
    const auto &req = requestHandler.handleRequest(message);
    if (!req.success)
    {
        return responseGenerator.generateJsonErrorResponse("Parsing error");
    }
    if (req.seat && req.theater && req.movie)
    {
        bool reserved_succesfully = db->reserveSeat(*req.movie, *req.theater, *req.seat);
        const auto &seats = db->getSeatsByMovieAndTheater(*req.movie, *req.theater);
        if (!seats)
        {
            return responseGenerator.generateJsonErrorResponse("Movie or theater not found");
        }
        return responseGenerator.generateJsonSeatsResponse(*req.movie, *req.theater, *seats, reserved_succesfully);
    }
    else if (req.theater && req.movie)
    {
        const auto &seats = db->getSeatsByMovieAndTheater(*req.movie, *req.theater);
        if (!seats)
        {
            return responseGenerator.generateJsonErrorResponse("Movie or theater not found");
        }
        return responseGenerator.generateJsonSeatsResponse(*req.movie, *req.theater, *seats);
    }
    else if (req.movie)
    {
        const auto &theaters = db->getTheatersByMovie(*req.movie);
        if (!theaters)
        {
            return responseGenerator.generateJsonErrorResponse("Movie not found");
        }
        return responseGenerator.generateJsonTheatersResponse(*req.movie, *theaters);
    }
    else if (!req.movie && !req.theater && !req.seat)
    {
        const auto &movies = db->getMovies();
        return responseGenerator.generateJsonMoviesResponse(movies);
    }
    return responseGenerator.generateJsonErrorResponse("Unknown error");
}
