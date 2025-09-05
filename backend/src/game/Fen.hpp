#pragma once

#include "Game.hpp"
#include <string>



class FEN
{
public:
    static void load(Game& board, const std::string& fen);
    static std::string toString(Game& game);
};