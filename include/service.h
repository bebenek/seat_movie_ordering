#pragma once

#include <string>
#include <memory>
#include "database.h"
#include "request_handler.h"
#include "response_generator.h"

class Service
{
public:
    Service(std::shared_ptr<Database> db);
    std::string process_message(const std::string &message);

private:
    std::shared_ptr<Database> db;
    RequestHandler requestHandler;
    ResponseGenerator responseGenerator;
};