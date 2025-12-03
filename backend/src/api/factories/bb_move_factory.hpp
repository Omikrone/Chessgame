#pragma once

#include "api/models/move.hpp"
#include "game/game_constants.hpp"

/**
 * @brief Factory class for creating BitboardMove objects from MoveRequest.
 *
 */
class BitboardMoveFactory {
   private:
    /**
     * @brief Converts a square in algebraic notation to an integer index.
     *
     * @param square The square in algebraic notation (e.g., "e4").
     * @return The integer index of the square (0-63).
     */
    static int square_to_int(const std::string& square);

   public:
    /**
     * @brief Creates a BitboardMove from the given MoveRequest.
     *
     * @param request The MoveRequest to convert.
     * @return The created BitboardMove object.
     */
    static BitboardMove from_move_request(const MoveRequest& request);
};