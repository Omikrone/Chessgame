#include "Game.hpp"


Game::Game(crow::SimpleApp& app) {
    _board = new GameBoard();
    _board.initBoard();
    _moveGenerator = new MoveGenerator(_board);
    _moveValidator = new MoveValidator(_board);
    _currentTurn = Color::WHITE;
    _blackMovesNb = 0;
    _whiteMovesNb = 0;
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
    Piece piece = _board.getPieceAt(move.initPos);
    std::vector<Move> rawMoves = rawMoves_moveGenerator.getRawPossibleMoves(&piece);
    std::vector<Move> legalMoves = _moveValidator.filterLegalMoves(rawMoves);
    return legalMoves;
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

GameBoard& Game::getGameBoard() const {
    return _board;
}

int Game::getNbMoves(Color side) const {
    if (side == Color::WHITE) return _whiteMovesNb;
    else return _blackMovesNb;
}