#pragma once

#include "piece.hpp"
#include "utils/constants.hpp"

#include <vector>
#include <cstdint>


class Bishop: public Piece {

    public:
        Bishop(Type pieceType, const Square &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<std::vector<Square>> getRawMoves() const override {
            return getBishopMoves(_position);
        }

        static std::vector<std::vector<Square>> getBishopMoves(const Square &currentPosition) {
            std::vector<std::vector<Square>> possibleMoves;

            int8_t count = 1;
            std::vector<Square> directionMoves;
            while ((currentPosition.file + count) < BOARD_LENGTH && (currentPosition.rank + count) < BOARD_LENGTH)
            {
                directionMoves.push_back({currentPosition.file + count, currentPosition.rank + count});
                count++;
            }
            possibleMoves.push_back(directionMoves);

            count = 1;
            directionMoves.clear();
            while ((currentPosition.file - count) >= 0 && (currentPosition.rank + count) < BOARD_LENGTH)
            {
                directionMoves.push_back({currentPosition.file - count, currentPosition.rank + count});
                count++;
            }
            possibleMoves.push_back(directionMoves);

            count = 1;
            directionMoves.clear();
            while ((currentPosition.file + count) < BOARD_LENGTH && (currentPosition.rank - count) >= 0)
            {
                directionMoves.push_back({currentPosition.file + count, currentPosition.rank - count});
                count++;
            }
            possibleMoves.push_back(directionMoves);

            count = 1;
            directionMoves.clear();
            while ((currentPosition.file - count) >= 0 && (currentPosition.rank - count) >= 0)
            {
                directionMoves.push_back({currentPosition.file - count, currentPosition.rank - count});
                count++;
            }
            possibleMoves.push_back(directionMoves);

            return possibleMoves;
        }
  
        Piece* clone() const override {
            return new Bishop(*this);
        }

        char toFEN() const override {
            if (_color == Color::WHITE) return 'B';
            else return 'b';
        }

};