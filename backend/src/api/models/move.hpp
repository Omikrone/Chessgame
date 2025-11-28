#pragma once

#include "crow/json.h"
#include <string>
#include <optional>


struct MoveRequest
{
    int game_id;
    std::string from;
    std::string to;
    std::optional<std::string> promotion;
};
