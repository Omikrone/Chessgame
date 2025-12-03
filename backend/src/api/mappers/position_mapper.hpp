#pragma once

#include "api/models/position.hpp"

#include "game.hpp"


/**
 * @brief Class for mapping game state to position response.
 * 
 */
class PositionMapper {
    public:
        /**
         * @brief Maps the game state and FEN to a PositionResponse.
         * 
         * @param game_state The current state of the game.
         * @param fen The FEN string representing the position.
         * @param current_turn The color of the player whose turn it is.
         * @return The mapped PositionResponse.
         */
        static PositionResponse to_position_response(const GameState game_state, const std::string& fen, Color current_turn);
};