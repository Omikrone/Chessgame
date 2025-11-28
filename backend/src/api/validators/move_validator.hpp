#pragma once

#include "square_validator.hpp"

#include "crow/json.h"
#include <string>
#include <vector>


class MoveValidator {
    public:
        static std::vector<std::string> validate(const crow::json::rvalue& data);
}; 