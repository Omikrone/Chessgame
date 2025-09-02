#include "Game.hpp"


Game::Game()
    : _board(),
      _moveGenerator(_board),
      _moveValidator(_board),
      _currentTurn(Color::WHITE),
      _blackMovesNb(0),
      _whiteMovesNb(0)
{
    _board.initBoard();
}



bool Game::applyMove(const Move& move) {
    std::vector<Move> legalMoves = getLegalMoves(move.initPos);
    for (Move m: legalMoves) {
        if (m == move) {
            _board.makeMove(move);
            return true;
        }
    }
    return false;
}


std::vector<Move> Game::getLegalMoves(Square sq) {
    Piece *piece = _board.getPieceAt(sq);
    std::vector<Move> rawMoves = _moveGenerator.getPossibleMoves(piece);

    std::vector<Move> ennemyMoves;
    if (piece->_color == Color::WHITE) ennemyMoves = _moveGenerator.getAllPossibleMoves(Color::BLACK);
    else ennemyMoves = _moveGenerator.getAllPossibleMoves(Color::WHITE);

    std::vector<Move> legalMoves = _moveValidator.filterLegalMoves(rawMoves, ennemyMoves);
    return legalMoves;
}


GameState Game::getGameState() {
    for (auto row: _board._board) {
        for (auto cell: row) {
            if (cell != nullptr && cell->_color == _currentTurn) {
                std::vector<Move> possibleMoves = _moveGenerator.getPossibleMoves(cell);
                if (!possibleMoves.empty()) return GameState::CONTINUING;
            }
        }
    }

    
    std::vector<Move> ennemyMoves;
    if (_currentTurn == Color::WHITE) ennemyMoves = _moveGenerator.getAllPossibleMoves(Color::BLACK);
    else ennemyMoves = _moveGenerator.getAllPossibleMoves(Color::WHITE);

    King& king = _board.getKing(_currentTurn);
    if (_board.isSquareAttacked(ennemyMoves, king._position)) return GameState::CHECKMATE;
    else return GameState::STALEMATE;
}

GameBoard& Game::getGameBoard() {
    return _board;
}

int Game::getNbMoves(Color side) const {
    if (side == Color::WHITE) return _whiteMovesNb;
    else return _blackMovesNb;
}