#pragma once

#include <iostream>

#include "pieces/piece.hpp"
#include "pieces/type.hpp"
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
    Position *_whiteKingPos;
    Position *_blackKingPos;

    GameBoard() {}

    void initBoard() {
        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            _board[1][i] = new Pawn(Type::PAWN, {i, 1}, Color::WHITE);
        }
        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            _board[6][i] = new Pawn(Type::PAWN, {i, 6}, Color::BLACK);
        }

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
        
        _board[0][3] = new Queen(Type::QUEEN, {3, 0}, Color::WHITE);
        _board[7][3] = new Queen(Type::QUEEN, {3, 7}, Color::BLACK);

        _board[0][4] = new King(Type::KING, {4, 0}, Color::WHITE);
        _board[7][4] = new King(Type::KING, {4, 7}, Color::BLACK);
        _blackKingPos = &_board[7][4]->_position;
        _whiteKingPos = &_board[0][4]->_position;
    }


    std::vector<Position> getLegalMoves(Position piecePosition) {
        std::vector<std::vector<Position>> rawMoves = _board[piecePosition.rank][piecePosition.file]->getPossibleMoves();

        Piece *piece = _board[piecePosition.rank][piecePosition.file];
        std::vector<Position> legalMoves;

        if (piece->_pieceType == Type::PAWN) {

            if (rawMoves.size() > 0) {
                for (Position p: rawMoves[0]) {
                    Piece *presentPiece = _board[p.rank][p.file];
                    if (presentPiece != nullptr && presentPiece->_color == piece->_color) {
                        break;
                    }
                    else {
                        legalMoves.push_back(p);
                    }
                }
            }

            if (rawMoves.size() > 1) {
                for (int i = 1; i < rawMoves.size(); i++)
                {
                    Position takePosition = rawMoves[i][0];
                    Piece *presentPiece = _board[takePosition.file][takePosition.rank];
                    if (presentPiece != nullptr && presentPiece->_color != piece->_color)
                    {
                        legalMoves.push_back(takePosition);
                    }
                }
            }
            
        }
        else {
            for (std::vector<Position> dm: rawMoves)
            {
                for (Position p: dm) {
                    Piece *presentPiece = _board[p.rank][p.file];
                    if (presentPiece != nullptr && presentPiece->_color == piece->_color) {
                        break;
                    }
                    else {
                        legalMoves.push_back(p);
                    }
                }
            }
        }

        return legalMoves;
    }

    std::vector<Position> filterCheckMoves(Position *piecePosition, std::vector<Position> possibleMoves) {
        std::vector<Position> legalMoves;
        std::vector<std::vector<Piece *>> simulatedBoard;
        Piece *piece = _board[piecePosition->rank][piecePosition->file];

        for (Position p: possibleMoves) {
            simulatedBoard = _board;
            if (!isKingInCheck(piece->_color, simulatedBoard)) {
                legalMoves.push_back(p);
            }
        }
        return legalMoves;
    }

    bool isKingInCheck(Color kingColor, std::vector<std::vector<Piece*>> board) {
        Piece *king;
        if (kingColor == Color::BLACK) king = board[_blackKingPos->rank][_blackKingPos->file];
        else king = board[_whiteKingPos->rank][_whiteKingPos->file];

        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            for (int8_t j = 0; j < BOARD_LENGTH; j++)
            {
                if (board[i][j] == nullptr || board[i][j]->_color == king->_color) continue;
                else {
                    std::vector<Position> possibleMoves = getLegalMoves({j, i});
                    for (Position p: possibleMoves)
                    {
                        if (p == king->_position) {
                            return true;
                        }
                    }
                    
                } 
            }
        }
        return false;
    }


    void makeMove(Position piecePosition, Position destination) {
        Piece *piece = _board[piecePosition.rank][piecePosition.file];
        _board[destination.rank][destination.file] = piece;
        _board[piecePosition.rank][piecePosition.file] = nullptr;
        piece->_position = {destination.file, destination.rank};
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


    void printBoard() {
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