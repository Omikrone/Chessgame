#pragma once

#include "piece.hpp"
#include "utils/constants.hpp"

#include <vector>
#include <cstdint>


class Rook: public Piece {

    public:
        Rook(Type pieceType, const Square &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<std::vector<Square>> getRawMoves() const override {
            return getRookMoves(_position);
        }

        static std::vector<std::vector<Square>> getRookMoves(const Square &currentPosition) {
            std::vector<std::vector<Square>> possibleMoves;

            // Direction to the top
            std::vector<Square> directionMoves;
            for (std::int8_t i = currentPosition.rank + 1; i < BOARD_LENGTH; i++)
            {
                directionMoves.push_back({currentPosition.file, i});
            }
            possibleMoves.push_back(directionMoves);

            // Direction to the bottom
            directionMoves.clear();
            for (std::int8_t i = currentPosition.rank - 1; i >= 0; i--)
            {
                directionMoves.push_back({currentPosition.file, i});
            }
            possibleMoves.push_back(directionMoves);

            // Direction to the left
            directionMoves.clear();
            for (std::int8_t i = currentPosition.file - 1; i >= 0; i--)
            {
                directionMoves.push_back({i, currentPosition.rank});
            }
            possibleMoves.push_back(directionMoves);

            // Direction to the right
            directionMoves.clear();
            for (std::int8_t i = currentPosition.file + 1; i < BOARD_LENGTH; i++)
            {
                directionMoves.push_back({i, currentPosition.rank});
            }
            possibleMoves.push_back(directionMoves);

            return possibleMoves;
        }

        std::unique_ptr<Piece> clone() const override {
            return std::make_unique<Rook>(*this);
        }
        
        char toFEN() const override {
            if (_color == Color::WHITE) return 'R';
            else return 'r';
        }
};