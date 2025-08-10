#pragma once

#include "piece.hpp"
#include "constants.hpp"

#include <vector>
#include <cstdint>


class King: public Piece {

    public:
        King(Type pieceType, const Position &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<std::vector<Position>> getPossibleMoves() const override {
            std::vector<std::vector<Position>> possibleMoves;
            std::vector<Position> directionMoves;

            for (std::int8_t i = -1; i <= 1; i++)
            {
                for (std::int8_t j = -1; j <= 1; j++)
                {
                    if (j == 0 && i == 0) continue;

                    int8_t newX = _position.file + i;
                    int8_t newY = _position.rank + j;

                    if (newX >= 0 && newX < BOARD_LENGTH &&
                        newY >= 0 && newY < BOARD_LENGTH) {
                        directionMoves.push_back({newX, newY});
                        possibleMoves.push_back(directionMoves);
                        directionMoves.clear();
                    }
                }
                
            }
            return possibleMoves;
        }

        Piece* clone() const override {
            return new King(*this);
        }

        char toFEN() const override {
            if (_color == Color::WHITE) return 'K';
            else return 'k';
        }

};