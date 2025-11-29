#pragma once

#include "api/models/position.hpp"

#include "game.hpp"


class PositionMapper {
    public:
        static PositionResponse to_position_response(const GameState game_state, const std::string& fen, Color current_turn);
};