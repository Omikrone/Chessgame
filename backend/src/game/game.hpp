#pragma once

#include "board/Board.hpp"
#include "move/MoveGenerator.hpp
#include "move/MoveValidator.hpp"
#include "board/pieces/utils/color.hpp"
#include "board/pieces/utils/Square.hpp"
#include "board/pieces/utils/GameState.hpp"


class Game
{
private:    
    GameBoard& _board;
    MoveGenerator& _moveGenerator;
    MoveValidator& _moveValidator;
    Color _currentTurn;
    int _blackMovesNb;
    int _whiteMovesNb;
public:
    Game();
    ~Game();
    GameState getGameState();
    bool applyMove(const Move& move);
    std::vector<Move> getLegalMoves(Square sq) const;
    Color getCurrentTurn() const;
    GameBoard& getGameBoard() const;
    int getNbMoves(Color side) const;
};