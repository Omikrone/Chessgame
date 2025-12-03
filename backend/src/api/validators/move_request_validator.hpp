#pragma once

#include "api/models/move.hpp"
#include "api/validators/square_validator.hpp"
#include "api/exceptions/game_exception.hpp"


/**
 * @brief Class for validating move requests.
 * 
 */
class MoveRequestValidator {
    public:
    
        /**
         * @brief Validates the given move request.
         * 
         * @param request The move request to validate.
         */
        static void validate(const MoveRequest& request);
};