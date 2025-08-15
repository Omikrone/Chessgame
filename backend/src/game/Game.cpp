#include "Game.hpp"


Game::Game(crow::SimpleApp& app) {
    _board = new GameBoard();
    _board.initBoard();
    _moveGenerator = new MoveGenerator(_board);
    _moveValidator = new MoveValidator(_board);
    _currentTurn = Color::WHITE;
    _blackMoves = 0;
    _whiteMoves = 0;
}


GameState Game::getGameState() {
    for (auto row: _board->_board) {
        for (auto cell: row) {
            if (cell != nullptr && cell->_color == _currentTurn) {
                std::vector<Move> possibleMoves = _moveGenerator->getPossibleMoves(_board->_board, {cell->_position.file, cell->_position.rank});
                if (!possibleMoves.empty()) return GameState::CONTINUING;
            }
        }
    }
    if (_moveGenerator->isKingInCheck(_currentTurn, _board->_board)) return GameState::CHECKMATE;
    else return GameState::STALEMATE;
}
