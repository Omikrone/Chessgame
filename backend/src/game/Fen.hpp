#pragma once

#include "game/game.hpp"
#include <string>


class FEN
{
public:
    static std::string to_string(Game& game);
};