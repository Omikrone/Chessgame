#pragma once

#include "game/board/board.hpp"
#include "game/components/move.hpp"


class MoveGenerator
{
    public:
        static std::vector<Move> get_all_possible_moves(GameBoard& board, Color side);
        static std::vector<Move> get_possible_moves(GameBoard& board, Piece *piece);
};
