#pragma once

#include "piece.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "constants.hpp"

#include <vector>
#include <cstdint>


class Queen: public Piece {

    public:
        Queen(Type pieceType, const Position &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<std::vector<Position>> getPossibleMoves() const override {
            std::vector<std::vector<Position>> possibleMoves = Bishop::getBishopMoves(_position);
            std::vector<std::vector<Position>> rookMoves = Rook::getRookMoves(_position);

            possibleMoves.insert(possibleMoves.end(), rookMoves.begin(), rookMoves.end());
            return possibleMoves;
        }

        char toFEN() const override {
            if (_color == Color::WHITE) return 'Q';
            else return 'q';
        }
};