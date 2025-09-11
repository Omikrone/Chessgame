#pragma once

#include <string>
#include "crow.h"


class DataValidator {
public:

    struct Result
    {
        bool valid;
        std::string error;
    }; 

    static Result isMessageValid(const crow::json::rvalue& data);
};
