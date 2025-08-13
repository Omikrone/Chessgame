#pragma once

#include <iostream>

#include "pieces/utils/type.hpp"
#include "pieces/utils/move.hpp"
#include "pieces/piece.hpp"
#include "pieces/pawn.hpp"
#include "pieces/rook.hpp"
#include "pieces/bishop.hpp"
#include "pieces/knight.hpp"
#include "pieces/king.hpp"
#include "pieces/queen.hpp"


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
        const Position knightPositions[] = {{1, 7}, {6, 7}, {6, 0}, {1, 0}};
        for (int8_t i = 0; i < 4; i++) {
            Position startPosition = {knightPositions[i].file, knightPositions[i].rank};
            if (i < 2) {
                _board[startPosition.rank][startPosition.file] = new Knight(Type::KNIGHT, startPosition, Color::BLACK);
            }
            else {
                _board[startPosition.rank][startPosition.file] = new Knight(Type::KNIGHT, startPosition, Color::WHITE);
            }
        }

        // Bishops initialization
        const Position bishopPositions[] = {{2, 7}, {5, 7}, {5, 0}, {2, 0}};
        for (int8_t i = 0; i < 4; i++) {
            Position startPosition = {bishopPositions[i].file, bishopPositions[i].rank};
            if (i < 2) {
                _board[startPosition.rank][startPosition.file] = new Bishop(Type::BISHOP, startPosition, Color::BLACK);
            }
            else {
                _board[startPosition.rank][startPosition.file] = new Bishop(Type::BISHOP, startPosition, Color::WHITE);
            }
        }

        // Rooks initialization
        const Position rookPositions[] = {{0, 7}, {7, 7}, {7, 0}, {0, 0}};
        for (int8_t i = 0; i < 4; i++) {
            Position startPosition = {rookPositions[i].file, rookPositions[i].rank};
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


    void makeMove(std::vector<std::vector<Piece*>> &board, Move pieceMovement) {
        Piece *piece = board[pieceMovement.initPos.rank][pieceMovement.initPos.file];

        if (pieceMovement.type == MoveType::CASTLE_KINGSIDE) {
            KingSideCastle(board, piece);
        }
        else if (pieceMovement.type == MoveType::CASTLE_QUEENSIDE) QueenSideCastle(board, piece);
        else if (pieceMovement.type == MoveType::EN_PASSANT) EnPassant(board, piece, pieceMovement);
        else {
            
            // Piece displacement
            board[pieceMovement.destPos.rank][pieceMovement.destPos.file] = piece;
            board[pieceMovement.initPos.rank][pieceMovement.initPos.file] = nullptr;
            piece->_position = {pieceMovement.destPos.file, pieceMovement.destPos.rank};
        }
        if (pieceMovement.type == MoveType::PROMOTION) {
            board[piece->_position.rank][piece->_position.file] = new Queen(Type::QUEEN, piece->_position, piece->_color);
            delete piece;
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

    void EnPassant(std::vector<std::vector<Piece*>> &board, Piece *pawn, Move move) {
            
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

    void KingSideCastle(std::vector<std::vector<Piece*>> &board, Piece *king) {

        // Rook displacement
        board[king->_position.rank][king->_position.file + 1] = board[king->_position.rank][king->_position.file + 3];
        board[king->_position.rank][king->_position.file + 3] = nullptr;
        board[king->_position.rank][king->_position.file + 1]->_position = {static_cast<int8_t>(king->_position.file + 1), king->_position.rank};

        // King displacement
        board[king->_position.rank][king->_position.file] = nullptr;
        board[king->_position.rank][king->_position.file + 2] = king;
        king->_position = {static_cast<int8_t>(king->_position.file + 2), king->_position.rank};
    }

    void QueenSideCastle(std::vector<std::vector<Piece*>> &board, Piece *king) {

        // Rook displacement
        board[king->_position.rank][king->_position.file - 1] = board[king->_position.rank][king->_position.file - 4];
        board[king->_position.rank][king->_position.file - 4] = nullptr;
        board[king->_position.rank][king->_position.file - 1]->_position = {static_cast<int8_t>(king->_position.file - 1), king->_position.rank};

        // King displacement
        board[king->_position.rank][king->_position.file] = nullptr;
        board[king->_position.rank][king->_position.file - 2] = king;
        king->_position = {static_cast<int8_t>(king->_position.file - 2), king->_position.rank};
        
    }


    std::string toFEN() {
        std::string fen;

        for (int8_t i=BOARD_LENGTH - 1; i >= 0; i--) {
            int8_t wo_piece = 0;
            for (int8_t j=0; j < BOARD_LENGTH; j++) {
                if (_board[i][j] != nullptr) {
                    if (wo_piece != 0) {
                        fen.append(std::to_string(wo_piece));
                        wo_piece = 0;
                    }
                    fen.push_back(_board[i][j]->toFEN());
                }
                else {
                    wo_piece++;
                }
            }
            if (wo_piece != 0) fen.append(std::to_string(wo_piece));
            fen.push_back('/');
        }
        fen.pop_back(); // Remove the last '/'
        return fen;
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
};