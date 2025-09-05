#pragma once

#include "board/Board.hpp"
#include "move/MoveGenerator.hpp"
#include "move/MoveValidator.hpp"
#include "board/pieces/utils/color.hpp"
#include "board/pieces/utils/Square.hpp"
#include "board/pieces/utils/GameState.hpp"


class Game
{
private:    
    GameBoard _board;
    MoveGenerator _moveGenerator;
    MoveValidator _moveValidator;
    Color _currentTurn;
    int _blackMovesNb;
    int _whiteMovesNb;
public:
    Game();
    ~Game() = default;
    bool applyMove(const Move& move);
    std::vector<Move> getLegalMoves(Square sq);
    GameState getGameState();
    Color getCurrentTurn() const;
    GameBoard& getGameBoard();
    int getNbMoves(Color side) const;
};