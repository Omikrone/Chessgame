#pragma once

#include "piece.hpp"
#include "constants.hpp"

#include <vector>
#include <cstdint>


class King: public Piece {

    public:
        King(Type pieceType, const Position &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<Position> getPossibleMoves() const override {
            std::vector<Position> possibleMoves;

            for (std::int8_t i = -1; i <= 1; i++)
            {
                for (std::int8_t j = 0; j <= 1; j++)
                {
                    if (j == 0 && i == 0) continue;

                    int8_t newX = _position.file + i;
                    int8_t newY = _position.rank + j;

                    if (newX >= 0 && newX < BOARD_LENGTH &&
                        newY >= 0 && newY < BOARD_LENGTH) {
                        possibleMoves.push_back({newX, newY});
                    }
                }
                
            }
            return possibleMoves;
        }

        char symbol() const override {
            return 'K';
        }

};