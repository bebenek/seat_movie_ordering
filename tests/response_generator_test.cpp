#include <vector>
#include "gtest/gtest.h"
#include "response_generator.h"

TEST(responseTest, generateJsonMoviesResponse)
{
    // GIVEN
    ResponseGenerator response_generator;
    std::vector<std::string> movies = {"1", "2", "3"};

    // WHEN
    const auto &response = response_generator.generateJsonMoviesResponse(movies);

    // THEN
    EXPECT_EQ(response, "{\"movies\":[\"1\",\"2\",\"3\"]}");
}

TEST(responseTest, generateJsonTheatersResponse)
{
    // GIVEN
    ResponseGenerator response_generator;
    std::vector<std::string> theaters = {"1", "2", "3"};
    std::string movie = "1";

    // WHEN
    const auto &response = response_generator.generateJsonTheatersResponse(movie, theaters);

    // THEN
    EXPECT_EQ(response, "{\"movie\":\"1\",\"theaters\":[\"1\",\"2\",\"3\"]}");
}

TEST(responseTest, generateJsonSeatsResponse)
{
    // GIVEN
    ResponseGenerator response_generator;
    std::vector<std::string> seats = {"1", "2", "3"};
    std::string movie = "1";
    std::string theater = "2";

    // WHEN
    const auto &response = response_generator.generateJsonSeatsResponse(movie, theater, seats);

    // THEN
    EXPECT_EQ(response, "{\"movie\":\"1\",\"theater\":\"2\",\"seats\":[\"1\",\"2\",\"3\"]}");
}

TEST(responseTest, generateJsonSeatsResponseWithReservedValue)
{
    // GIVEN
    ResponseGenerator response_generator;
    std::vector<std::string> seats = {"1", "2", "3"};
    std::string movie = "1";
    std::string theater = "2";
    bool reserved = true;

    // WHEN
    const auto &response = response_generator.generateJsonSeatsResponse(movie, theater, seats, reserved);

    // THEN
    EXPECT_EQ(response, "{\"reserved_successfully\":true,\"movie\":\"1\",\"theater\":\"2\",\"seats\":[\"1\",\"2\",\"3\"]}");
}

TEST(responseTest, generateJsonErrorResponse)
{
    // GIVEN
    ResponseGenerator response_generator;
    int error_code = 1;

    // WHEN
    const auto &response = response_generator.generateJsonErrorResponse("error");

    // THEN
    EXPECT_EQ(response, "{\"error_message\":\"error\"}");
}