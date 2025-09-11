#include "Game.hpp"


Game::Game()
    : _board(),
      _history(),
      _moveValidator(_board, _history),
      _currentTurn(Color::WHITE),
      _blackMovesNb(0),
      _whiteMovesNb(0)
{}



bool Game::tryApplyMove(const Move& move) {
    Piece *piece = _board.getPieceAt(move.initPos);
    if (piece == nullptr || piece->_color != _currentTurn) return false;

    std::vector<Move> legalMoves = getLegalMoves(move.initPos);
    for (Move m: legalMoves) {
        if (m == move) {
            _board.makeMove(m);
            _history.push(m);
            return true;
        }
    }
    return false;
}


std::vector<Move> Game::getLegalMoves(Square sq) {
    Piece *piece = _board.getPieceAt(sq);
    if (piece == nullptr) {
        std::cout << "Piece doesn't exists";
        return std::vector<Move>{};
    }
    std::vector<Move> rawMoves = MoveGenerator::getPossibleMoves(_board, piece);

    std::vector<Move> legalMoves = _moveValidator.filterLegalMoves(rawMoves, piece->_color);
    return legalMoves;
}


GameState Game::getGameState() {
    for (auto& row: _board._board) {
        for (const auto &cell: row) {
            if (cell != nullptr && cell->_color == _currentTurn) {
                std::vector<Move> possibleMoves = MoveGenerator::getPossibleMoves(_board, cell.get());
                std::vector<Move> legalMoves = _moveValidator.filterLegalMoves(possibleMoves, cell.get()->_color);
                if (!legalMoves.empty()) return GameState::CONTINUING;
            }
        }
    }
    
    std::vector<Move> enemyMoves;
    if (_currentTurn == Color::WHITE) enemyMoves = MoveGenerator::getAllPossibleMoves(_board, Color::BLACK);
    else enemyMoves = MoveGenerator::getAllPossibleMoves(_board, Color::WHITE);

    King& king = _board.getKing(_currentTurn);
    if (_board.isSquareAttacked(enemyMoves, king._position)) return GameState::CHECKMATE;
    else return GameState::STALEMATE;
}

GameBoard& Game::getGameBoard() {
    return _board;
}

int Game::getNbMoves(Color side) const {
    if (side == Color::WHITE) return _whiteMovesNb;
    else return _blackMovesNb;
}


void Game::nextTurn() {
    _currentTurn = (_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;
}


Color Game::getCurrentTurn() const {
    return _currentTurn;
}