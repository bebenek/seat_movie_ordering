#include <iostream>

#include "gtest/gtest.h"
#include "service.h"

class ServiceTest : public ::testing::Test
{

protected:
    std::shared_ptr<Service> service_;

    void SetUp() override
    {
        std::shared_ptr<Database> db = std::make_shared<Database>();
        db->addShow("m1", "t1", seats1);
        db->addShow("m1", "t2", seats2);
        db->addShow("m2", "t2", seats1);
        service_ = std::make_shared<Service>(db);
    }

    virtual void TearDown()
    {
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

TEST_F(ServiceTest, no_json_request)
{
    EXPECT_EQ(service_->processMessage("Hello World!"), "{\"error_message\":\"Parsing error\"}");
}

TEST_F(ServiceTest, empty_json_request)
{
    EXPECT_EQ(service_->processMessage("{}"), "{\"movies\":[\"m1\",\"m2\"]}");
}

TEST_F(ServiceTest, movie_json_request)
{
    EXPECT_EQ(service_->processMessage("{\"movie\": \"1\"}"), "{\"error_message\":\"Movie not found\"}");
    EXPECT_EQ(service_->processMessage("{\"movie\": \"m1\"}"), "{\"movie\":\"m1\",\"theaters\":[\"t1\",\"t2\"]}");
}

TEST_F(ServiceTest, movie_theather_json_request)
{
    EXPECT_EQ(service_->processMessage("{\"movie\": \"1\", \"theater\": \"1\"}"), "{\"error_message\":\"Movie or theater not found\"}");
    EXPECT_EQ(service_->processMessage("{\"movie\": \"m1\", \"theater\": \"t1\"}"), "{\"movie\":\"m1\",\"theater\":\"t1\",\"seats\":[\"C3\",\"C4\",\"D3\",\"D4\",\"E3\",\"E4\"]}");
}

TEST_F(ServiceTest, movie_theather_seat_json_request)
{
    EXPECT_EQ(service_->processMessage("{\"movie\": \"m1\", \"theater\": \"1\", \"seat\": \"A1\"}"), "{\"error_message\":\"Movie or theater not found\"}");
    EXPECT_EQ(service_->processMessage("{\"movie\": \"m1\", \"theater\": \"t1\", \"seat\": \"A1\"}"), "{\"reserved_successfully\":false,\"movie\":\"m1\",\"theater\":\"t1\",\"seats\":[\"C3\",\"C4\",\"D3\",\"D4\",\"E3\",\"E4\"]}");
    EXPECT_EQ(service_->processMessage("{\"movie\": \"m1\", \"theater\": \"t1\", \"seat\": \"E4\"}"), "{\"reserved_successfully\":true,\"movie\":\"m1\",\"theater\":\"t1\",\"seats\":[\"C3\",\"C4\",\"D3\",\"D4\",\"E3\"]}");
}