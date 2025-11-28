#pragma once

#include "crow/json.h"
#include <string>
#include <optional>


struct MoveRequest
{
    int game_id;
    std::string from;
    std::string to;
    std::optional<char> promotion;
};

struct BitboardMove
{
    int from;
    int to;
    std::optional<char> promotion;
};