#pragma once

#include "piece.hpp"
#include "constants.hpp"

#include <vector>
#include <cstdint>


class Rook: public Piece {

    public:
        Rook(Type pieceType, const Position &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<Position> getPossibleMoves() const override {
            return getRookMoves(_position);
        }

        static std::vector<Position> getRookMoves(const Position &currentPosition) {
            std::vector<Position> possibleMoves;

            for (std::int8_t i = 0; i < BOARD_LENGTH; i++)
            {
                if (i != currentPosition.file) possibleMoves.push_back({i, currentPosition.rank});
            }

            for (std::int8_t j = 0; j < BOARD_LENGTH; j++)
            {
                if (j != currentPosition.rank) possibleMoves.push_back({currentPosition.file, j});
            }

            return possibleMoves;
        }

        
        char symbol() const override {
            return 'R';
        }

};