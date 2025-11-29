#pragma once

#include "api/exceptions/game_exception.hpp"

#include "crow/json.h"
#include <string>
#include <vector>


class MoveJsonValidator {
    public:
        static void validate(const crow::json::rvalue& data);
}; 