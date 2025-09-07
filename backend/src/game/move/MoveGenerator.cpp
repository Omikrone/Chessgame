
#include "../board/Board.hpp"
#include "../board/pieces/utils/move.hpp"
#include "MoveGenerator.hpp"
    

MoveGenerator::MoveGenerator(GameBoard& board) : _board(board) {}


std::vector<Move> MoveGenerator::getAllPossibleMoves(Color side) {
    std::vector<Move> allPossibleMoves;

    for (auto& rank: _board._board) {
        for (const auto& cell: rank) {
            if (cell != nullptr && cell->_color == side) {
                std::vector<Move> possibleMoves = getPossibleMoves(cell.get());
                allPossibleMoves.insert(allPossibleMoves.end(), possibleMoves.begin(), possibleMoves.end());
            }
        }
    }
    return allPossibleMoves;
}

std::vector<Move> MoveGenerator::getPossibleMoves(Piece *piece) {

    std::vector<std::vector<Square>> rawMoves = piece->getRawMoves();
    std::vector<Move> rawPossibleMoves;

    if (piece->_pieceType == Type::PAWN) {

        for (std::vector<Square> dm: rawMoves) {
            if (dm.empty()) continue;

            // Forward
            if (dm[0].file == piece->_position.file) {
                for (Square p: dm) {
                    Piece *presentPiece = _board._board[p.rank][p.file].get();
                    if (presentPiece != nullptr) {
                        break;
                    }
                    else if (p.rank == BOARD_LENGTH - 1 || p.rank == 0) {
                        rawPossibleMoves.push_back({piece->_position, p, MoveType::PROMOTION, false});
                    }
                    else {
                        rawPossibleMoves.push_back({piece->_position, p, MoveType::NORMAL, false});
                    }
                }
            }

            // Side take
            else {
                Square takePosition = dm[0];
                Piece *presentPiece = _board._board[takePosition.rank][takePosition.file].get();
                if (presentPiece != nullptr && presentPiece->_color != piece->_color)
                {
                    if (takePosition.rank == BOARD_LENGTH - 1 || takePosition.rank == 0) {
                        rawPossibleMoves.push_back({piece->_position, takePosition, MoveType::PROMOTION, true});
                    }
                    else {
                        rawPossibleMoves.push_back({piece->_position, takePosition, MoveType::NORMAL, true});
                    }
                }
                else if (takePosition.rank == BOARD_LENGTH - 1 || takePosition.rank == 0) {
                    
                }
                /*else if (_history.size() > 0 && checkEnPassant(board, piece, &takePosition, _history.back())) {
                    rawPossibleMoves.push_back({piece->_position, takePosition, MoveType::EN_PASSANT, true});
                }*/
            }
        }
    }
    else if (piece->_pieceType == Type::KING) {
        for (std::vector<Square> dm: rawMoves)
        {
            for (Square p: dm) {
                int8_t distance  = p.file - piece->_position.file;
                Piece *presentPiece = _board._board[p.rank][p.file].get();
                if (distance == 2) rawPossibleMoves.push_back({piece->_position, p, MoveType::CASTLE_KINGSIDE});
                else if (distance == -2) rawPossibleMoves.push_back({piece->_position, p, MoveType::CASTLE_QUEENSIDE});
                else if (presentPiece != nullptr && presentPiece->_color == piece->_color) {
                    break;
                }
                else if (presentPiece != nullptr && presentPiece->_color != piece->_color) {
                    rawPossibleMoves.push_back({piece->_position, p, MoveType::NORMAL, true});
                    break;
                }
                else {
                    rawPossibleMoves.push_back({piece->_position, p, MoveType::NORMAL, false});
                }
            }
        }
    }
    else {

        for (std::vector<Square> dm: rawMoves)
        {
            for (Square p: dm) {
                Piece *presentPiece = _board._board[p.rank][p.file].get();
                if (presentPiece != nullptr && presentPiece->_color == piece->_color) {
                    break;
                }
                else if (presentPiece != nullptr && presentPiece->_color != piece->_color) {
                    rawPossibleMoves.push_back({piece->_position, p, MoveType::NORMAL, true});
                    break;
                }
                else {
                    rawPossibleMoves.push_back({piece->_position, p, MoveType::NORMAL, false});
                }
            }
        }
    }
    return rawPossibleMoves;
}