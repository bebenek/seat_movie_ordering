#include <iostream>

#include "gtest/gtest.h"
#include "service.h"

namespace {
class ServiceTest : public ::testing::Test
{

protected:
    std::shared_ptr<Service> service_;

    void SetUp() override
    {
        std::shared_ptr<Database> db = std::make_shared<Database>();
        service_ = std::make_shared<Service>(db);
    }

    virtual void TearDown()
    {
    }
};

TEST_F(ServiceTest, sample_test)
{
    EXPECT_EQ(1, 1);
}

TEST_F(ServiceTest, sample_test_2)
{
    EXPECT_EQ(service_->process_message("Hello World!"), "Hello World!");
}
} // namespace