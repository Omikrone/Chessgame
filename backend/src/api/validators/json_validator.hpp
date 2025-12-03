#pragma once

#include "api/exceptions/game_exception.hpp"

#include "crow/json.h"
#include <string>
#include <vector>


/**
 * @brief Class for validating JSON data.
 * 
 */
class JsonValidator {
    public:
    
        /**
         * @brief Validates the given JSON data.
         * 
         * @param data The JSON data to validate.
         */
        static void validate(const crow::json::rvalue& data);
}; 