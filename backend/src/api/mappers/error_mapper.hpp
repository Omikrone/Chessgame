#pragma once

#include "api/models/error.hpp"
#include "api/exceptions/game_exception.hpp"


/**
 * @brief Class for mapping exceptions to error responses.
 * 
 */
class ErrorMapper {
    public:
        /**
         * @brief Maps a GameException to an ErrorResponse.
         * 
         * @param exception The GameException to map.
         * @return The mapped ErrorResponse.
         */
        static ErrorResponse to_error_response(const GameException& exception);
};