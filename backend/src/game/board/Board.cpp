#pragma once

#include <iostream>

#include "Board.hpp"


class GameBoard {
public:

    std::vector<std::vector<Piece*>> _board =
        std::vector<std::vector<Piece*>>(BOARD_LENGTH, std::vector<Piece*>(BOARD_LENGTH, nullptr));

    GameBoard() {}


    void initBoard() {

        // Pawns initialization
        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            _board[1][i] = new Pawn(Type::PAWN, {i, 1}, Color::WHITE);
        }
        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            _board[6][i] = new Pawn(Type::PAWN, {i, 6}, Color::BLACK);
        }

        // Knights initialization
        const Square knightPositions[] = {{1, 7}, {6, 7}, {6, 0}, {1, 0}};
        for (int8_t i = 0; i < 4; i++) {
            Square startPosition = {knightPositions[i].file, knightPositions[i].rank};
            if (i < 2) {
                _board[startPosition.rank][startPosition.file] = new Knight(Type::KNIGHT, startPosition, Color::BLACK);
            }
            else {
                _board[startPosition.rank][startPosition.file] = new Knight(Type::KNIGHT, startPosition, Color::WHITE);
            }
        }

        // Bishops initialization
        const Square bishopPositions[] = {{2, 7}, {5, 7}, {5, 0}, {2, 0}};
        for (int8_t i = 0; i < 4; i++) {
            Square startPosition = {bishopPositions[i].file, bishopPositions[i].rank};
            if (i < 2) {
                _board[startPosition.rank][startPosition.file] = new Bishop(Type::BISHOP, startPosition, Color::BLACK);
            }
            else {
                _board[startPosition.rank][startPosition.file] = new Bishop(Type::BISHOP, startPosition, Color::WHITE);
            }
        }

        // Rooks initialization
        const Square rookPositions[] = {{0, 7}, {7, 7}, {7, 0}, {0, 0}};
        for (int8_t i = 0; i < 4; i++) {
            Square startPosition = {rookPositions[i].file, rookPositions[i].rank};
            if (i < 2) {
                _board[startPosition.rank][startPosition.file] = new Rook(Type::ROOK, startPosition, Color::BLACK);
            }
            else {
                _board[startPosition.rank][startPosition.file] = new Rook(Type::ROOK, startPosition, Color::WHITE);
            }
        }
        
        // Queens initialization
        _board[0][3] = new Queen(Type::QUEEN, {3, 0}, Color::WHITE);
        _board[7][3] = new Queen(Type::QUEEN, {3, 7}, Color::BLACK);

        // Kings initialization
        _board[0][4] = new King(Type::KING, {4, 0}, Color::WHITE);
        _board[7][4] = new King(Type::KING, {4, 7}, Color::BLACK);
    }


    Piece getPieceAt(Square sq) {
        return _board[sq.rank][sq.file];
    }


    void makeMove(const Move& move) {
        Piece *piece = board[pieceMovement.initPos.rank][pieceMovement.initPos.file];

        switch (move.type)
        {
            case MoveType::CASTLE_KINGSIDE:
                KingSideCastle(board, piece);
                break;

            case MoveType::CASTLE_QUEENSIDE:
                QueenSideCastle(board, piece);
                break;

            case MoveType::EN_PASSANT:
                EnPassant(board, piece, pieceMovement);
                break;

            case MoveType::PROMOTION:
                movePiece(move.initPos, move.destPos)
                board[piece->_position.rank][piece->_position.file] = new Queen(Type::QUEEN, piece->_position, piece->_color);
                delete piece;
        
            default:
                movePiece(move.initPos, move.destPos);
                break;
        }
    }

    Piece *findKing(std::vector<std::vector<Piece*>> &board, Color kingColor) {
        for (auto& row : board) {
            for (auto& cell : row) {
                if (cell != nullptr && cell->_pieceType == Type::KING && cell->_color == kingColor) {
                    return cell;
                }
            }
        }
        return nullptr;
    }

    void enPassant(std::vector<std::vector<Piece*>> &board, Piece *pawn, Move move) {
            
        // Pawn displacement
        board[move.destPos.rank][move.destPos.file] = pawn;
        board[move.initPos.rank][move.initPos.file] = nullptr;

        // Other pawn destruction
        if (pawn->_color == Color::WHITE) {
            board[move.destPos.rank - 1][move.destPos.file] = nullptr;
            delete board[move.destPos.rank - 1][move.destPos.file];
        }
        else {
            board[move.destPos.rank + 1][move.destPos.file] = nullptr;
            delete board[move.destPos.rank + 1][move.destPos.file];
        }
        pawn->_position = {move.destPos.file, move.destPos.rank};
    }


    void kingSideCastle(std::vector<std::vector<Piece*>> &board, Piece *king) {

        // Rook displacement
        board[king->_position.rank][king->_position.file + 1] = board[king->_position.rank][king->_position.file + 3];
        board[king->_position.rank][king->_position.file + 3] = nullptr;
        board[king->_position.rank][king->_position.file + 1]->_position = {static_cast<int8_t>(king->_position.file + 1), king->_position.rank};

        // King displacement
        board[king->_position.rank][king->_position.file] = nullptr;
        board[king->_position.rank][king->_position.file + 2] = king;
        king->_position = {static_cast<int8_t>(king->_position.file + 2), king->_position.rank};
    }


    void queenSideCastle(std::vector<std::vector<Piece*>> &board, Piece *king) {

        // Rook displacement
        board[king->_position.rank][king->_position.file - 1] = board[king->_position.rank][king->_position.file - 4];
        board[king->_position.rank][king->_position.file - 4] = nullptr;
        board[king->_position.rank][king->_position.file - 1]->_position = {static_cast<int8_t>(king->_position.file - 1), king->_position.rank};

        // King displacement
        board[king->_position.rank][king->_position.file] = nullptr;
        board[king->_position.rank][king->_position.file - 2] = king;
        king->_position = {static_cast<int8_t>(king->_position.file - 2), king->_position.rank};
    }


    void printBoard(std::vector<std::vector<Piece*>> board) {
        for (int8_t j = BOARD_LENGTH - 1; j >= 0; j--)
        {
            for (int8_t i = 0; i < BOARD_LENGTH; i++)
            {
                if (_board[j][i] != nullptr) {
                    std::cout << " " << _board[j][i]->toFEN() << " ";
                }
                else {
                    std::cout << "   ";
                }
            }
            std::cout << std::endl;
        }
    }

    
    bool isKingInCheck(Color kingColor, std::vector<std::vector<Piece*>> board) {
        Piece *king = _board->findKing(board, kingColor);
        if (!king) {
            std::cerr << "Erreur : Roi introuvable !" << std::endl;
            return false;
        }

        return isSquareAttacked(king->_position, board, king->_color);
    }


    bool isSquareAttacked(Square position, std::vector<std::vector<Piece*>> board, Color color) {
        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            for (int8_t j = 0; j < BOARD_LENGTH; j++)
            {
                if (board[i][j] == nullptr || board[i][j]->_color == color) continue;
                else {
                    std::vector<Move> possibleMoves = getLegalMoves(board, {j, i});
                    for (Move m: possibleMoves)
                    {
                        if (m.destPos == position) {
                            return true;
                        }
                    }
                    
                } 
            }
        }
        return false;
    }

private:

    void movePiece(Square from, Square to) {
            
        // Piece displacement
        board[to.rank][to.file] = board[from.rank][from.file];
        board[from.rank][from.file] = nullptr;
        piece->_position = to;
    }

    void promotion(Square pawnSq, Type pieceType) {

        delete _board[pawnSq.rank][pawnSq.file];
        Color pawnColor = _board[pawnSq.rank][pawnSq.file]->_color;
        Piece *newPiece;

        switch (pieceType)
        {

        case Type::ROOK:
            newPiece = new Rook(pieceType, pawnSq, pawnColor);
            break;

        case Type::BISHOP:
            newPiece = new Bishop(pieceType, pawnSq, pawnColor);
            break;

        case Type::KNIGHT:
            newPiece = new Knight(pieceType, pawnSq, pawnColor);
            break;
        
        default:
            newPiece = new Queen(pieceType, pawnSq, pawnColor);
            break;
        }

        _board[pawnSq.rank][pawnSq.file] = newPiece;
    }
};