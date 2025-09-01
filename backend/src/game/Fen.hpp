#pragma once

#include "Game.hpp"



class FEN
{
public:
    static void load(Game& board, const std::string& fen);
    static std::string toString(const Game& board);
};