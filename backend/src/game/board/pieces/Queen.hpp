#pragma once

#include "piece.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "utils/constants.hpp"

#include <vector>
#include <cstdint>


class Queen: public Piece {

    public:
        Queen(Type pieceType, const Square &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<std::vector<Square>> getRawMoves() const override {
            std::vector<std::vector<Square>> possibleMoves = Bishop::getBishopMoves(_position);
            std::vector<std::vector<Square>> rookMoves = Rook::getRookMoves(_position);

            possibleMoves.insert(possibleMoves.end(), rookMoves.begin(), rookMoves.end());
            return possibleMoves;
        }

        Piece* clone() const override {
            return new Queen(*this);
        }

        char toFEN() const override {
            if (_color == Color::WHITE) return 'Q';
            else return 'q';
        }
};