#pragma once

#include <string>
#include <memory>
#include "database.h"
#include "request_handler.h"

class Service
{
public:
    Service(std::shared_ptr<Database> db);
    ~Service();
    const std::string& process_message(const std::string& message);
private:
std::shared_ptr<Database> db_;
RequestHandler request_handler_;
};