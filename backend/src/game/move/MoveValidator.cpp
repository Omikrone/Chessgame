#include "MoveValidator.hpp"


MoveValidator::MoveValidator(GameBoard& gameBoard) : _board(gameBoard) {}


std::vector<Move>& MoveValidator::filterLegalMoves(std::vector<Move>& rawPossibleMoves, std::vector<Move>& ennemyPossibleMoves) {

    std::vector<Move> withoutCastleMoves = filterCastleMoves(rawPossibleMoves, ennemyPossibleMoves);
    std::vector<Move> legalMoves = filterCheckMoves(withoutCastleMoves, ennemyPossibleMoves);  
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


std::vector<Move>& MoveValidator::filterCheckMoves(std::vector<Move>& possibleMoves, std::vector<Move>& ennemyPossibleMoves) {
    std::vector<Move> legalMoves;
    std::vector<std::vector<Piece *>> simulatedBoard;

    for (Move m: possibleMoves) {
        Piece *piece = _board.getPieceAt(m.initPos);
        simulatedBoard = deepCopyBoard(_board._board);
        _board.makeMove(m); // INTEGRER LA SIMULATION DE BOARD (DEEP COPY)
        
        King& king = _board.getKing(piece->_color);
        if (!_board.isSquareAttacked(ennemyPossibleMoves, king._position)) {
            legalMoves.push_back(m);
        }
        
        for (auto& row : simulatedBoard) {
            for (auto& cell : row) {
                delete cell;
            }
        }
    }
    return legalMoves;
}


std::vector<Move>& MoveValidator::filterCastleMoves(std::vector<Move>& possibleMoves, std::vector<Move>& ennemyPossibleMoves) {
    std::vector<Move> legalMoves;

    for (Move m: possibleMoves) {
        Piece *piece = _board.getPieceAt(m.initPos);
        if (m.type == MoveType::CASTLE_KINGSIDE) {
            if (checkKingSideCastle(piece, ennemyPossibleMoves)) legalMoves.push_back(m);
        }
        else if (m.type == MoveType::CASTLE_QUEENSIDE) {
            if (checkQueenSideCastle(piece, ennemyPossibleMoves)) legalMoves.push_back(m);
        }
        else {
            legalMoves.push_back(m);
        }
    }
    return legalMoves;
}


bool MoveValidator::checkKingSideCastle(Piece *king, std::vector<Move>& ennemyPossibleMoves) {
    if (king->_hasMoved) return false;
    Piece *rook = _board._board[king->_position.rank][king->_position.file + 3];
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
    Piece *rook = _board._board[king->_position.rank][king->_position.file - 4];
    if (rook == nullptr || rook->_hasMoved) return false;
    if (_board.isSquareAttacked(ennemyPossibleMoves, king->_position)) return false;
    for (int8_t f = 1; f < king->_position.file; f++)
    {
        if (_board._board[king->_position.rank][f] != nullptr || _board.isSquareAttacked(ennemyPossibleMoves, {f, king->_position.rank})) return false;
    }
    return true;
}

    
std::vector<std::vector<Piece*>> deepCopyBoard(const std::vector<std::vector<Piece*>>& board) {
    std::vector<std::vector<Piece*>> copy(board.size(), std::vector<Piece*>(board[0].size(), nullptr));

    for (int8_t r = 0; r < board.size(); r++) {
        for (int8_t f = 0; f < board[r].size(); f++) {
            if (board[r][f] != nullptr) {
                copy[r][f] = board[r][f]->clone();
            }
        }
    }
    return copy;
}
