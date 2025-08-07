#pragma once

#include "piece.hpp"
#include "constants.hpp"

#include <vector>
#include <cstdint>


class Bishop: public Piece {

    public:
        Bishop(Type pieceType, const Position &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<Position> getPossibleMoves() const override {
            return getBishopMoves(_position);
        }

        static std::vector<Position> getBishopMoves(const Position &currentPosition) {
            std::vector<Position> possibleMoves;

            int8_t count = 1;
            while ((currentPosition.file + count) < BOARD_LENGTH && (currentPosition.rank + count) < BOARD_LENGTH)
            {
                possibleMoves.push_back({currentPosition.file + count, currentPosition.rank + count});
                count++;
            }

            count = 1;
            while ((currentPosition.file - count) >= 0 && (currentPosition.rank + count) < BOARD_LENGTH)
            {
                possibleMoves.push_back({currentPosition.file - count, currentPosition.rank + count});
                count++;
            }

            count = 1;
            while ((currentPosition.file + count) < BOARD_LENGTH && (currentPosition.rank - count) >= 0)
            {
                possibleMoves.push_back({currentPosition.file + count, currentPosition.rank - count});
                count++;
            }

            count = 1;
            while ((currentPosition.file - count) >= 0 && (currentPosition.rank - count) >= 0)
            {
                possibleMoves.push_back({currentPosition.file - count, currentPosition.rank - count});
                count++;
            }

            return possibleMoves;
        }

        char symbol() const override {
            return 'B';
        }

};