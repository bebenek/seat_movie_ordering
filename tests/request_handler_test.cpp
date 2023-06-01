#include <iostream>

#include "gtest/gtest.h"
#include "request_handler.h"

const std::string ONE = "1";
const std::string TWO = "2";
const std::string THREE = "3";

TEST(requestTest, no_json_request)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "Hello World!";

    // WHEN
    const auto &req = request_handler.handle_request(request);

    // THEN
    EXPECT_EQ(req.movie, boost::none);
    EXPECT_EQ(req.theater, boost::none);
    EXPECT_EQ(req.seat, boost::none);
    EXPECT_FALSE(req.success);
}

TEST(requestTest, empty_json_request)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{}";

    // WHEN
    const auto &req = request_handler.handle_request(request);

    // THEN
    EXPECT_EQ(req.movie, boost::none);
    EXPECT_EQ(req.theater, boost::none);
    EXPECT_EQ(req.seat, boost::none);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_movie)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"movie\": \"1\"}";

    // WHEN
    const auto &req = request_handler.handle_request(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_EQ(req.theater, boost::none);
    EXPECT_EQ(req.seat, boost::none);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_movie_and_theater)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"movie\": \"1\", \"theater\": \"2\"}";

    // WHEN
    const auto &req = request_handler.handle_request(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_EQ(req.theater, TWO);
    EXPECT_EQ(req.seat, boost::none);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_movie_and_theater_and_seat)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"movie\": \"1\", \"theater\": \"2\", \"seat\": \"3\"}";

    // WHEN
    const auto &req = request_handler.handle_request(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_EQ(req.theater, TWO);
    EXPECT_EQ(req.seat, THREE);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_movie_and_seat)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"movie\": \"1\", \"seat\": \"3\"}";

    // WHEN
    const auto &req = request_handler.handle_request(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_EQ(req.theater, boost::none);
    EXPECT_EQ(req.seat, boost::none);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_with_theater_and_seat)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"theater\": \"2\", \"seat\": \"3\"}";

    // WHEN
    const auto &req = request_handler.handle_request(request);

    // THEN
    EXPECT_EQ(req.movie, boost::none);
    EXPECT_EQ(req.theater, boost::none);
    EXPECT_EQ(req.seat, boost::none);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_all_data_different_order)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"seat\": \"3\", \"movie\": \"1\", \"theater\": \"2\"}";

    // WHEN
    const auto &req = request_handler.handle_request(request);

    // THEN
    EXPECT_EQ(req.movie, ONE);
    EXPECT_EQ(req.theater, TWO);
    EXPECT_EQ(req.seat, THREE);
    EXPECT_TRUE(req.success);
}

TEST(requestTest, json_request_all_data_movie_number)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"seat\": \"3\", \"movie\": 1, \"theater\": \"2\"}";

    // WHEN
    const auto &req = request_handler.handle_request(request);

    // THEN
    EXPECT_EQ(req.movie, boost::none);
    EXPECT_EQ(req.theater, boost::none);
    EXPECT_EQ(req.seat, boost::none);
    EXPECT_FALSE(req.success);
}

TEST(requestTest, json_request_all_data_seat_number)
{
    // GIVEN
    RequestHandler request_handler;
    std::string request = "{\"seat\": 3, \"movie\": \"1\", \"theater\": \"2\"}";

    // WHEN
    const auto &req = request_handler.handle_request(request);

    // THEN
    EXPECT_EQ(req.movie, boost::none);
    EXPECT_EQ(req.theater, boost::none);
    EXPECT_EQ(req.seat, boost::none);
    EXPECT_FALSE(req.success);
}