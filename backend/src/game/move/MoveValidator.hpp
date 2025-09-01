#pragma once

#include <vector>

#include "../board/pieces/utils/Move.hpp"
#include "../board/pieces/Piece.hpp"
#include "../board/Board.hpp"


class MoveValidator
{
private:
    GameBoard& _board;
    bool checkKingSideCastle(Piece& king);
    bool checkQueenSideCastle(Piece& king);
    bool checkEnPassant(Piece& pawn);
    std::vector<Move>& filterCastleMoves(std::vector<Move>& rawPossibleMoves);
    std::vector<Move>& filterCheckMoves(std::vector<Move>& rawPossible Moves);
public:
    MoveValidator(GameBoard& board);
    ~MoveValidator();
    std::vector<Move>& filterLegalMoves(std::vector<Move>& rawPossibleMoves);
};