#pragma once

#include "piece.hpp"
#include "utils/constants.hpp"

#include <vector>
#include <cstdint>


class Knight: public Piece {

    public:
        Knight(Type pieceType, const Square &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}


    std::vector<std::vector<Square>> getRawMoves() const override {
        std::vector<std::vector<Square>> possibleMoves;
        std::vector<Square> directionMoves;

        const int8_t dx[] = { 2,  1, -1, -2, -2, -1,  1,  2 };
        const int8_t dy[] = { 1,  2,  2,  1, -1, -2, -2, -1 };

        for (int8_t i = 0; i < 8; ++i) {
            int8_t newX = _position.file + dx[i];
            int8_t newY = _position.rank + dy[i];

            if (newX >= 0 && newX < BOARD_LENGTH &&
                newY >= 0 && newY < BOARD_LENGTH) {
                directionMoves.push_back({static_cast<int8_t>(newX), static_cast<int8_t>(newY)});
                possibleMoves.push_back(directionMoves);
                directionMoves.clear();
            }
        }

        return possibleMoves;
    }

    Piece* clone() const override {
        return new Knight(*this);
    }

    char toFEN() const override {
        if (_color == Color::WHITE) return 'N';
        else return 'n';
    }
};