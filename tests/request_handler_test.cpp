#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "request_handler.h"
#include <boost/optional/optional_io.hpp>

const std::string ONE("1");
const std::string TWO("2");
const std::vector<std::string> THREE = {"3"};

TEST(requestTest, no_json_request)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "Hello World!";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_FALSE(req.movie);
    EXPECT_FALSE(req.theater);
    EXPECT_FALSE(req.seats);
    EXPECT_FALSE(req.success);
}

TEST(requestTest, empty_json_request)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{}";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_FALSE(req.movie);
    EXPECT_FALSE(req.theater);
    EXPECT_FALSE(req.seats);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_movie)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"movie\": \"1\"}";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_FALSE(req.theater);
    EXPECT_FALSE(req.seats);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_movie_and_theater)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"movie\": \"1\", \"theater\": \"2\"}";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_EQ(req.theater, TWO);
    EXPECT_FALSE(req.seats);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_movie_and_theater_and_seat)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"movie\": \"1\", \"theater\": \"2\", \"seats\": [\"3\"]}";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_EQ(req.theater, TWO);
    ASSERT_TRUE(req.seats);
    EXPECT_EQ(*req.seats, THREE);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_movie_and_theater_and_seat_not_array)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"movie\": \"1\", \"theater\": \"2\", \"seats\": \"3\"}";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_FALSE(req.movie);
    EXPECT_FALSE(req.theater);
    EXPECT_FALSE(req.seats);
    EXPECT_FALSE(req.success);
}

TEST(requestTest, json_request_with_movie_and_theater_and_seat_array)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"movie\": \"1\", \"theater\": \"2\", \"seats\": [\"3\", \"4\"]}";
    std::vector<std::string> seats{"3", "4"};

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_EQ(req.theater, TWO);
    ASSERT_TRUE(req.seats);
    EXPECT_EQ(*req.seats, seats);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_movie_and_seat)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"movie\": \"1\", \"seats\": [\"3\"]}";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_FALSE(req.theater);
    EXPECT_FALSE(req.seats);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_theater_and_seat)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"theater\": \"2\", \"seats\": \"3\"}";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_FALSE(req.movie);
    EXPECT_FALSE(req.theater);
    EXPECT_FALSE(req.seats);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_all_data_different_order)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"seats\": [\"3\"], \"movie\": \"1\", \"theater\": \"2\"}";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_EQ(req.theater, TWO);
    ASSERT_TRUE(req.seats);
    EXPECT_EQ(*req.seats, THREE);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_all_data_movie_number)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"seats\": [\"3\"], \"movie\": 1, \"theater\": \"2\"}";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_FALSE(req.movie);
    EXPECT_FALSE(req.theater);
    EXPECT_FALSE(req.seats);
    EXPECT_FALSE(req.success);
}

TEST(requestTest, json_request_all_data_seat_number)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"seats\": [3], \"movie\": \"1\", \"theater\": \"2\"}";

    // WHEN
    const auto &req = request_handler.handleRequest(request);

    // THEN
    EXPECT_FALSE(req.movie);
    EXPECT_FALSE(req.theater);
    EXPECT_FALSE(req.seats);
    EXPECT_FALSE(req.success);
}