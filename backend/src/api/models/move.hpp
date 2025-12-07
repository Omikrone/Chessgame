#pragma once

#include <optional>
#include <string>

#include "crow/json.h"
#include "game/game_constants.hpp"

/**
 * @brief Struct representing a move request from the client.
 *
 */
struct MoveRequest {
    int game_id;
    std::string msg_type;
    std::string from;
    std::string to;
    std::optional<char> promotion;
};

/**
 * @brief Struct representing a move in bitboard format.
 *
 */
struct BitboardMove {
    int from;
    int to;
    std::optional<PieceType> promotion;
};