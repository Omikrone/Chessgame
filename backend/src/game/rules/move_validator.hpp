#pragma once

#include <vector>

#include "game/components/move.hpp"
#include "game/pieces/piece.hpp"
#include "game/board/Board.hpp"
#include "game/rules/move_generator.hpp"
#include "game/game_history.hpp"


class MoveValidator
{
private:
    GameBoard& _board;
    GameHistory& _history;
    bool checkKingSideCastle(Piece *king, std::vector<Move>& ennemyPossibleMoves);
    bool checkQueenSideCastle(Piece *king, std::vector<Move>& ennemyPossibleMoves);
    std::vector<Move> filterEnPassantMoves(std::vector<Move>& possibleMoves, Color side);
    std::vector<Move> filterCastleMoves(std::vector<Move>& possibleMoves, Color side);
    std::vector<Move> filterCheckMoves(std::vector<Move>& possibleMoves, Color side);
public:
    MoveValidator(GameBoard& board, GameHistory& history);
    ~MoveValidator() = default;
    std::vector<Move> filterLegalMoves(std::vector<Move>& rawPossibleMoves, Color side);
};

std::vector<std::vector<Piece*>> deepCopyBoard(const std::vector<std::vector<Piece*>>& board);