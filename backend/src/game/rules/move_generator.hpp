#pragma once

#include "game/board/board.hpp"
#include "game/components/move.hpp"


class MoveGenerator
{
    public:
        static std::vector<Move> getAllPossibleMoves(GameBoard& board, Color side);
        static std::vector<Move> getPossibleMoves(GameBoard& board, Piece *piece);
};
