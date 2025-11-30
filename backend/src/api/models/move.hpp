#pragma once

#include "crow/json.h"
#include <string>
#include <optional>

#include "game/game_constants.hpp"


struct MoveRequest
{
    int game_id;
    std::string msg_type;
    std::string from;
    std::string to;
    std::optional<char> promotion;
};

struct BitboardMove
{
    int from;
    int to;
    std::optional<PieceType> promotion;
};