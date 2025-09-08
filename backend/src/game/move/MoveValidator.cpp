#include "MoveValidator.hpp"


MoveValidator::MoveValidator(GameBoard& gameBoard) : _board(gameBoard) {}


std::vector<Move> MoveValidator::filterLegalMoves(std::vector<Move>& rawPossibleMoves, Color side) {
    
    std::vector<Move> withoutCastleMoves = filterCastleMoves(rawPossibleMoves, side);
    std::vector<Move> legalMoves = filterCheckMoves(withoutCastleMoves, side);
    return legalMoves;
}


/*bool MoveValidator::filterEnPassantMoves(std::vector<Move>& rawPossibleMoves) {
    Piece *pieceToTake = _board._board[lastMove.destPos.rank][lastMove.destPos.file];
    if (pieceToTake == nullptr || pieceToTake->_color == piece->_color || pieceToTake->_pieceType != Type::PAWN) return false;
    int8_t distance = lastMove.destPos.rank - lastMove.initPos.rank;
    if (distance != 2 && distance != -2) return false;
    if (takePosition->file == pieceToTake->_position.file && piece->_position.rank == pieceToTake->_position.rank) return true;
}
EN PASSANT FOURNIR L'HISTORIQUE    
*/


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
    for (int8_t f = 1; f < king->_position.file; f++)
    {
        if (_board._board[king->_position.rank][f] != nullptr || _board.isSquareAttacked(ennemyPossibleMoves, {f, king->_position.rank})) return false;
    }
    return true;
}
