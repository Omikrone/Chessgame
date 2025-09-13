#pragma once

#include <string>

// Deactivate the warning of unreachable code in crow
#pragma warning(push)
#pragma warning(disable : 4702)
#include "crow.h"
#pragma warning(pop)


class DataValidator {
public:

    struct Result
    {
        bool valid;
        std::string error;
    }; 

    static Result is_message_valid(const crow::json::rvalue& data);
};
