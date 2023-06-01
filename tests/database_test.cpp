#include "database.h"
#include <memory>
#include "gtest/gtest.h"

class DatabaseTest : public ::testing::Test
{
protected:
    std::shared_ptr<Database> database_;
    void SetUp() override
    {
        database_ = std::make_shared<Database>();
        database_->addShow("m1", "t1", seats1);
        database_->addShow("m1", "t2", seats2);
        database_->addShow("m2", "t2", seats1);
    }

    Database::Seats seats1 = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 1, 0, 0}};
    std::vector<std::string> available_seats1 = {
        "C3", "C4",
        "D3", "D4",
        "E3", "E4"};
    Database::Seats seats2 = {
        {0, 0, 1, 1},
        {0, 0, 1, 1},
        {1, 1, 1, 0},
        {1, 1, 1, 1},
        {1, 1, 1, 1}};
    std::vector<std::string> available_seats2 = {
        "A1", "A2",
        "B1", "B2",
        "C4"};
};

TEST_F(DatabaseTest, add_show)
{
    // GIVEN
    Database::Seats seats = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0}};
    std::vector<std::string> available_seats = {
        "C2", "C3", "C4",
        "D2", "D3", "D4",
        "E2", "E3", "E4"};

    // WHEN
    database_->addShow("m3", "t3", seats);

    // THEN
    EXPECT_EQ(database_->getSeatsByMovieAndTheater("m3", "t3"), available_seats);
}

TEST_F(DatabaseTest, get_seats)
{
    // WHEN
    auto seats1 = database_->getSeatsByMovieAndTheater("m1", "t1");
    auto seats12 = database_->getSeatsByMovieAndTheater("m1", "t2");
    auto seats2 = database_->getSeatsByMovieAndTheater("m2", "t2");

    // THEN
    EXPECT_EQ(seats1, this->available_seats1);
    EXPECT_EQ(seats12, this->available_seats2);
    EXPECT_EQ(seats2, this->available_seats1);
}

TEST_F(DatabaseTest, reserve_seat)
{
    // GIVEN
    Database::Seats seats = {
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}};

    // WHEN
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"A1"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"A2"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"A3"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"A4"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"B1", "B2", "B3", "B4"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"C1"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"C2", "C3", "C4"}));
    EXPECT_TRUE(database_->reserveSeats("m1", "t1", {"C3"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"C3", "C4"}));
    EXPECT_TRUE(database_->reserveSeats("m1", "t1", {"C4"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"D1", "D2", "D3", "D4"}));
    EXPECT_TRUE(database_->reserveSeats("m1", "t1", {"D3", "D4"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"D3", "D4"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"D4"}));
    EXPECT_FALSE(database_->reserveSeats("m1", "t1", {"E1", "E2", "E3", "E4"}));
    EXPECT_TRUE(database_->reserveSeats("m1", "t1", {"E3", "E4"}));

    // THEN
    EXPECT_TRUE(database_->getSeatsByMovieAndTheater("m1", "t1")->empty());
    EXPECT_EQ(database_->getSeatsByMovieAndTheater("m1", "t2"), this->available_seats2);
    EXPECT_EQ(database_->getSeatsByMovieAndTheater("m2", "t2"), this->available_seats1);
}

TEST_F(DatabaseTest, get_movies)
{
    // GIVEN
    std::vector<std::string> movies = {"m1", "m2"};

    // WHEN
    auto movies_ = database_->getMovies();

    // THEN
    EXPECT_EQ(movies_, movies);
}

TEST_F(DatabaseTest, get_theaters_by_movie)
{
    // GIVEN
    std::vector<std::string> theaters1 = {"t1", "t2"};
    std::vector<std::string> theaters2 = {"t2"};

    // WHEN
    auto theaters1_ = database_->getTheatersByMovie("m1");
    auto theaters2_ = database_->getTheatersByMovie("m2");

    // THEN
    EXPECT_EQ(theaters1_, theaters1);
    EXPECT_EQ(theaters2_, theaters2);
}

TEST_F(DatabaseTest, get_theaters_by_missing_movie)
{
    // GIVEN

    // WHEN
    auto theaters1_ = database_->getTheatersByMovie("e1");

    // THEN
    EXPECT_FALSE(theaters1_);
}

TEST_F(DatabaseTest, get_seats_by_movie_and_missing_theater)
{
    // GIVEN

    // WHEN
    auto seats = database_->getSeatsByMovieAndTheater("m1", "e1");

    // THEN
    EXPECT_FALSE(seats);
}