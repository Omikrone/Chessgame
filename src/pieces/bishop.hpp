#pragma once

#include "piece.hpp"
#include "../board.hpp"

#include <vector>
#include <cstdint>


class Bishop: public Piece {

    public:
        Bishop(const Position &startPosition, Color color)
            : Piece(startPosition, color) {}

        std::vector<Position> getPossibleMoves() const override {
            getBishopMoves(_position);
        }

        static std::vector<Position> getBishopMoves(const Position &currentPosition) {
            std::vector<Position> possibleMoves;

            int8_t count = 1;
            while ((currentPosition.x + count) < BOARD_LENGTH && (currentPosition.y + count) < BOARD_LENGTH)
            {
                possibleMoves.push_back({currentPosition.x + count, currentPosition.y + count});
                count++;
            }

            count = 1;
            while ((currentPosition.x - count) >= 0 && (currentPosition.y + count) < BOARD_LENGTH)
            {
                possibleMoves.push_back({currentPosition.x - count, currentPosition.y + count});
                count++;
            }

            count = 1;
            while ((currentPosition.x + count) < BOARD_LENGTH && (currentPosition.y - count) >= 0)
            {
                possibleMoves.push_back({currentPosition.x + count, currentPosition.y - count});
                count++;
            }

            count = 1;
            while ((currentPosition.x - count) >= 0 && (currentPosition.y - count) >= 0)
            {
                possibleMoves.push_back({currentPosition.x - count, currentPosition.y - count});
                count++;
            }

            return possibleMoves;
        }

        char symbol() const override {
            return 'B';
        }

};