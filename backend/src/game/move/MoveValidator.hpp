#pragma once

#include <vector>

#include "../board/pieces/utils/Move.hpp"
#include "../board/pieces/Piece.hpp"
#include "../board/Board.hpp"


class MoveValidator
{
private:
    GameBoard& _board;
    bool checkKingSideCastle(Piece *king, std::vector<Move>& ennemyPossibleMoves);
    bool checkQueenSideCastle(Piece *king, std::vector<Move>& ennemyPossibleMoves);
    std::vector<Move> filterEnPassantMoves(std::vector<Move>& rawPossibleMoves);
    std::vector<Move> filterCastleMoves(std::vector<Move>& rawPossibleMoves, std::vector<Move>& ennemyPossibleMoves);
    std::vector<Move> filterCheckMoves(std::vector<Move>& rawPossibleMoves, std::vector<Move>& ennemyPossibleMoves);
public:
    MoveValidator(GameBoard& board);
    ~MoveValidator() = default;
    std::vector<Move> filterLegalMoves(std::vector<Move>& rawPossibleMoves, std::vector<Move>& ennemyPossibleMoves);
};

std::vector<std::vector<Piece*>> deepCopyBoard(const std::vector<std::vector<Piece*>>& board);