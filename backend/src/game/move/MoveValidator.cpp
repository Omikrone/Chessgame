#include "MoveValidator.hpp"


MoveValidator::MoveValidator(GameBoard& gameBoard, GameHistory& history) 
: _board(gameBoard),
  _history(history) {}


std::vector<Move> MoveValidator::filterLegalMoves(std::vector<Move>& rawPossibleMoves, Color side) {
    
    std::vector<Move> withoutCastleMoves = filterCastleMoves(rawPossibleMoves, side);
    std::vector<Move> withoutCheckMoves = filterCheckMoves(withoutCastleMoves, side);
    std::vector<Move> legalMoves = filterEnPassantMoves(withoutCheckMoves, side);
    return legalMoves;
}


std::vector<Move> MoveValidator::filterEnPassantMoves(std::vector<Move>& possibleMoves, Color side) {
    std::vector<Move> legalMoves;

    if (!_history.empty()) {
        const Move& lastMove = _history.last();
        Piece *pieceToTake = _board._board[lastMove.destPos.rank][lastMove.destPos.file].get();

        for (Move m: possibleMoves) {
            if (m.type == MoveType::EN_PASSANT) {
                Piece *piece = _board._board[m.initPos.rank][m.initPos.file].get();
                if (pieceToTake == nullptr || pieceToTake->_color == side || pieceToTake->_pieceType != Type::PAWN) continue;
                int8_t distance = lastMove.destPos.rank - lastMove.initPos.rank;
                if (distance != 2 && distance != -2) continue;
                if (lastMove.destPos.file == pieceToTake->_position.file && piece->_position.rank == pieceToTake->_position.rank) legalMoves.push_back(m);
            }
            else {
                legalMoves.push_back(m);
            }
        }
    }
    else {
        for (Move m: possibleMoves) {
            if (m.type != MoveType::EN_PASSANT) legalMoves.push_back(m);
        }
    }
    return legalMoves;
}


std::vector<Move> MoveValidator::filterCheckMoves(std::vector<Move>& possibleMoves, Color side) {
    std::vector<Move> legalMoves;

    for (Move m: possibleMoves) {
        std::unique_ptr<GameBoard> simulatedBoard = _board.clone();
        simulatedBoard.get()->makeMove(m);

        std::vector<Move> enemyMoves;
        Color enemyColor = (side == Color::WHITE) ? Color::BLACK : Color::WHITE;
        enemyMoves = MoveGenerator::getAllPossibleMoves(*simulatedBoard, enemyColor);
        
        King& king = simulatedBoard.get()->getKing(side);
        if (!simulatedBoard.get()->isSquareAttacked(enemyMoves, king._position)) {
            legalMoves.push_back(m);
        }
    }
    return legalMoves;
}


std::vector<Move> MoveValidator::filterCastleMoves(std::vector<Move>& possibleMoves, Color side) {
    std::vector<Move> legalMoves;
    std::vector<Move> enemyMoves;
    Color enemyColor = (side == Color::WHITE) ? Color::BLACK : Color::WHITE;
    enemyMoves = MoveGenerator::getAllPossibleMoves(_board, enemyColor);

    for (Move m: possibleMoves) {
        Piece *piece = _board.getPieceAt(m.initPos);
        if (m.type == MoveType::CASTLE_KINGSIDE) {
            if (checkKingSideCastle(piece, enemyMoves)) legalMoves.push_back(m);
        }
        else if (m.type == MoveType::CASTLE_QUEENSIDE) {
            if (checkQueenSideCastle(piece, enemyMoves)) legalMoves.push_back(m);
        }
        else {
            legalMoves.push_back(m);
        }
    }
    return legalMoves;
}


bool MoveValidator::checkKingSideCastle(Piece *king, std::vector<Move>& ennemyPossibleMoves) {
    if (king->_hasMoved) return false;
    Piece *rook = _board._board[king->_position.rank][king->_position.file + 3].get();
    if (rook == nullptr || rook->_hasMoved) return false;
    if (_board.isSquareAttacked(ennemyPossibleMoves, king->_position)) return false;
    for (int8_t f = BOARD_LENGTH - 2; f > king->_position.file; f--)
    {
        if (_board._board[king->_position.rank][f] != nullptr || _board.isSquareAttacked(ennemyPossibleMoves, {f, king->_position.rank})) {
            return false;
        }
    }
    return true;
}


bool MoveValidator::checkQueenSideCastle(Piece *king, std::vector<Move>& ennemyPossibleMoves) {
    if (king->_hasMoved) return false;
    Piece *rook = _board._board[king->_position.rank][king->_position.file - 4].get();
    if (rook == nullptr || rook->_hasMoved) return false;
    if (_board.isSquareAttacked(ennemyPossibleMoves, king->_position)) return false;
    for (int8_t f = 2; f < king->_position.file; f++)
    {
        if (_board._board[king->_position.rank][f] != nullptr || _board.isSquareAttacked(ennemyPossibleMoves, {f, king->_position.rank})) return false;
    }
    return true;
}
