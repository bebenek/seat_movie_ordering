
#include "service.h"

Service::Service(std::shared_ptr<Database> db) : db_(db), request_handler_()
{
}

Service::~Service()
{
}

const std::string& Service::process_message(const std::string& message)
{
    const auto& req = request_handler_.handle_request(message);
    if (req.seat) {
        return *req.movie;
    }
    return message;
}
