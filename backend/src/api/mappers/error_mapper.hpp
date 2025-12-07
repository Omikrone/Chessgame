#pragma once

#include "api/exceptions/game_exception.hpp"
#include "api/models/error.hpp"

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