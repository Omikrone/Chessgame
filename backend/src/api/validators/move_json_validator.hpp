#pragma once

#include "result.hpp"

#include "crow/json.h"
#include <string>
#include <vector>


class MoveJsonValidator {
    public:
        static Result<crow::json::rvalue> validate(const crow::json::rvalue& data);
}; 