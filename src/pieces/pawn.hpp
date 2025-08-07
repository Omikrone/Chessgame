#pragma once

#include "piece.hpp"
#include "constants.hpp"
#include "type.hpp"

#include <vector>
#include <cstdint>


class Pawn : public Piece {

    public:

        Pawn(Type pieceType, const Position &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<Position> getPossibleMoves() const override {
            std::vector<Position> possibleMoves;

            std::int8_t direction = static_cast<std::int8_t>(_color);

            if (_position.rank + direction >= 0 && _position.rank + direction < BOARD_LENGTH) {

                // Forward walk
                possibleMoves.push_back({_position.file, _position.rank + direction});

                if (_position.file > 0) {
                    // First side capture
                    possibleMoves.push_back({_position.file - 1, _position.rank + direction});
                }
                if (_position.file < BOARD_LENGTH - 1) {
                    // Second side capture
                    possibleMoves.push_back({_position.file + 1, _position.rank + direction});
                }
            }
            return possibleMoves;
        }

        char symbol() const override {
            return 'P';
        }
};