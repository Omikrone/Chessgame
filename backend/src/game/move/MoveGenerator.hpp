#pragma once

#include "../board/Board.hpp"
#include "../board/pieces/utils/Move.hpp"


class MoveGenerator
{
    public:
        static std::vector<Move> getAllPossibleMoves(GameBoard& board, Color side);
        static std::vector<Move> getPossibleMoves(GameBoard& board, Piece *piece);
};
