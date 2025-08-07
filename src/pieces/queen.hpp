#pragma once

#include "piece.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "../board.hpp"

#include <vector>
#include <cstdint>


class Queen: public Piece {

    public:
        Queen(Type pieceType, const Position &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<Position> getPossibleMoves() const override {
            std::vector<Position> possibleMoves = Bishop::getBishopMoves(_position);
            std::vector<Position> rookMoves = Rook::getRookMoves(_position);

            possibleMoves.insert(possibleMoves.end(), rookMoves.begin(), rookMoves.end());
            return possibleMoves;
        }

        char symbol() const override {
            return 'Q';
        }

};