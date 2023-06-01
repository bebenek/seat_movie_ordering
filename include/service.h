#pragma once

#include <string>
#include <memory>
#include "database.h"
#include "request_handler.h"
#include "response_generator.h"

/**
 * @brief The Service class is responsible for processing messages from the client.
 *
 */
class Service
{
public:
    Service(std::shared_ptr<Database> db);
    /**
     * @brief Process a message from the client.
     *
     * @param message The message from the client. Expecting JSON
     * @return std::string The response (JSON) to the client.
     */
    std::string processMessage(const std::string &message);

private:
    std::shared_ptr<Database> db;
    RequestHandler requestHandler;
    ResponseGenerator responseGenerator;
};