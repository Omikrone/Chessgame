#pragma once

#include "crow/json.h"
#include <string>


/**
 * @brief Class for validating chess squares.
 * 
 */
class SquareValidator {
    public:

        /**
         * @brief Validates if the given string is a valid chess square.
         * 
         * @param square The square string to validate.
         * @return true if the square is valid, else false.
         */
        static bool is_valid_square(const std::string& square);
};