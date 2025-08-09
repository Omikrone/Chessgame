#pragma once

#include "piece.hpp"
#include "constants.hpp"

#include <vector>
#include <cstdint>


class Knight: public Piece {

    public:
        Knight(Type pieceType, const Position &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}


    std::vector<std::vector<Position>> getPossibleMoves() const override {
        std::vector<std::vector<Position>> possibleMoves;
        std::vector<Position> directionMoves;

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

    char toFEN() const override {
        if (_color == Color::WHITE) return 'N';
        else return 'n';
    }
};