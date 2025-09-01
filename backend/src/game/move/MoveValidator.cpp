#include "MoveValidator.hpp"


std::vector<Move>& MoveValidator::filterLegalMoves(std::vector<Move>& rawPossibleMoves, Square piecePosition) {
    Piece *piece = _board._board[piecePosition.rank][piecePosition.file];

    std::vector<Move> withoutCastleMoves = filterCastleMoves(piece->_position, rawPossibleMoves);
    std::vector<Move> legalMoves = filterCheckMoves(piece->_position, withoutCastleMoves);  
    return legalMoves;
}


std::vector<Move>& MoveValidator::filterCheckMoves(std::vector<Move> possibleMoves) {
    std::vector<Move> legalMoves;
    std::vector<std::vector<Piece *>> simulatedBoard;

    for (Move m: possibleMoves) {
        Piece *piece = _board.getPieceAt(m.initPos);
        simulatedBoard = deepCopyBoard(_board._board);
        _board.makeMove(simulatedBoard, m);
        
        if (!isKingInCheck(piece->_color, simulatedBoard)) {
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


std::vector<Move>& MoveValidator::filterCastleMoves(Square *piecePosition, std::vector<Move> possibleMoves) {
    std::vector<Move> legalMoves;

    Piece *piece = _board->_board[piecePosition->rank][piecePosition->file];
    if (piece->_pieceType != Type::KING) return possibleMoves;

    for (Move m: possibleMoves) {
        if (m.type == MoveType::CASTLE_KINGSIDE) {
            if (checkKingSideCastle(piece)) legalMoves.push_back(m);
        }
        else if (m.type == MoveType::CASTLE_QUEENSIDE) {
            if (checkQueenSideCastle(piece)) legalMoves.push_back(m);
        }
        else {
            legalMoves.push_back(m);
        }
    }
    return legalMoves;
}


bool MoveValidator::checkKingSideCastle(Piece *king) {
    if (king->_hasMoved) return false;
    Piece *rook = _board->_board[king->_position.rank][king->_position.file + 3];
    if (rook == nullptr || rook->_hasMoved) return false;
    if (isSquareAttacked(king->_position, _board->_board, king->_color)) return false;
    for (int8_t f = BOARD_LENGTH - 2; f > king->_position.file; f--)
    {
        if (_board->_board[king->_position.rank][f] != nullptr || isSquareAttacked({f, king->_position.rank}, _board->_board, king->_color)) {
            return false;
        }
    }
    return true;
}

bool MoveValidator::checkQueenSideCastle(Piece *king) {
    if (king->_hasMoved) return false;
    Piece *rook = _board->_board[king->_position.rank][king->_position.file - 4];
    if (rook == nullptr || rook->_hasMoved) return false;
    if (isSquareAttacked(king->_position, _board->_board, king->_color)) return false;
    for (int8_t f = 1; f < king->_position.file; f++)
    {
        if (_board->_board[king->_position.rank][f] != nullptr || isSquareAttacked({f, king->_position.rank}, _board->_board, king->_color)) return false;
    }
    return true;
}


bool MoveValidator::checkEnPassant(std::vector<std::vector<Piece*>> board, Piece *piece, Square *takePosition, Move lastMove) {
    Piece *pieceToTake = board[lastMove.destPos.rank][lastMove.destPos.file];
    if (pieceToTake == nullptr || pieceToTake->_color == piece->_color || pieceToTake->_pieceType != Type::PAWN) return false;
    int8_t distance = lastMove.destPos.rank - lastMove.initPos.rank;
    if (distance != 2 && distance != -2) return false;
    if (takePosition->file == pieceToTake->_position.file && piece->_position.rank == pieceToTake->_position.rank) return true;
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
