
#include "service.h"
#include "database.h"

namespace
{
std::string processReservation(const RequestHandler::Request& req, std::shared_ptr<Database> db, const ResponseGenerator& responseGenerator)
{
    bool reserved_succesfully = db->reserveSeats(*req.movie, *req.theater, *req.seats);
    const auto &seats = db->getSeatsByMovieAndTheater(*req.movie, *req.theater);
    if (!seats)
    {
        return responseGenerator.generateJsonErrorResponse("Movie or theater not found");
    }
    return responseGenerator.generateJsonSeatsResponse(*req.movie, *req.theater, *seats, reserved_succesfully);
}

std::string processSeats(const RequestHandler::Request& req, std::shared_ptr<Database> db, const ResponseGenerator& responseGenerator)
{
    const auto &seats = db->getSeatsByMovieAndTheater(*req.movie, *req.theater);
    if (!seats)
    {
        return responseGenerator.generateJsonErrorResponse("Movie or theater not found");
    }
    return responseGenerator.generateJsonSeatsResponse(*req.movie, *req.theater, *seats);
}

std::string processTheater(const RequestHandler::Request& req, std::shared_ptr<Database> db, const ResponseGenerator& responseGenerator)
{
    const auto &theaters = db->getTheatersByMovie(*req.movie);
    if (!theaters)
    {
        return responseGenerator.generateJsonErrorResponse("Movie not found");
    }
    return responseGenerator.generateJsonTheatersResponse(*req.movie, *theaters);
}

std::string processMovie(std::shared_ptr<Database> db, const ResponseGenerator& responseGenerator)
{
    const auto &movies = db->getMovies();
    return responseGenerator.generateJsonMoviesResponse(movies);
}

}

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

    if (req.seats && req.theater && req.movie)
    {
        return processReservation(req, db, responseGenerator);
    }
    else if (req.theater && req.movie)
    {
        return processSeats(req, db, responseGenerator);
    }
    else if (req.movie)
    {
        return processTheater(req, db, responseGenerator);
    }
    else if (!req.movie && !req.theater && !req.seats)
    {
        return processMovie(db, responseGenerator);
    }
    return responseGenerator.generateJsonErrorResponse("Unknown error");
}
