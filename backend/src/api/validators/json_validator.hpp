#pragma once

#include "api/exceptions/game_exception.hpp"

#include "crow/json.h"
#include <string>
#include <vector>


class JsonValidator {
    public:
        static void validate(const crow::json::rvalue& data);
}; 