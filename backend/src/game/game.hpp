#pragma once

#include "board/Board.hpp"
#include "move/MoveGenerator.hpp
#include "move/MoveValidator.hpp"
#include "pieces/utils/color.hpp"
#include "pieces/utils/position.hpp"
#include "board/pieces/utils/GameState.hpp"


class Game
{
private:    
    GameBoard& _board;
    MoveGenerator& _moveGenerator;
    MoveValidator& _moveValidator;
    Color _currentTurn;
    int _blackMoves;
    int _whiteMoves;
public:
    Game();
    ~Game();
    GameState getGameState();
};