#include "response_generator.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

std::string ResponseGenerator::generateJsonMoviesResponse(const std::vector<std::string> &movies) const
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    writer.StartObject();
    writer.Key("movies");
    writer.StartArray();
    for (const auto &movie : movies)
    {
        writer.String(movie.c_str());
    }
    writer.EndArray();
    writer.EndObject();
    return buffer.GetString();
}

std::string ResponseGenerator::generateJsonTheatersResponse(const std::string& movie, const std::vector<std::string> &theaters) const
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    writer.StartObject();
    writer.Key("movie");
    writer.String(movie.c_str());
    writer.Key("theaters");
    writer.StartArray();
    for (const auto &theater : theaters)
    {
        writer.String(theater.c_str());
    }
    writer.EndArray();
    writer.EndObject();
    return buffer.GetString();
}

std::string ResponseGenerator::generateJsonSeatsResponse(const std::string& movie, const std::string& theater, const std::vector<std::string> &seats, boost::optional<bool> reserved_successfully) const
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    writer.StartObject();
    if (reserved_successfully)
    {
        writer.Key("reserved_successfully");
        writer.Bool(reserved_successfully.get());
    }
    writer.Key("movie");
    writer.String(movie.c_str());
    writer.Key("theater");
    writer.String(theater.c_str());
    writer.Key("seats");
    writer.StartArray();
    for (const auto &seat : seats)
    {
        writer.String(seat.c_str());
    }
    writer.EndArray();
    writer.EndObject();
    return buffer.GetString();
}

std::string ResponseGenerator::generateJsonErrorResponse(const std::string& errorMessage) const
{
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    writer.StartObject();
    writer.Key("error_message");
    writer.String(errorMessage.c_str());
    writer.EndObject();
    return buffer.GetString();
}