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

            if (_position.y + direction >= 0 && _position.y + direction < BOARD_LENGTH) {

                // Forward walk
                possibleMoves.push_back({_position.x, _position.y + direction});

                if (_position.x > 0) {
                    // First side capture
                    possibleMoves.push_back({_position.x - 1, _position.y + direction});
                }
                if (_position.x < BOARD_LENGTH - 1) {
                    // Second side capture
                    possibleMoves.push_back({_position.x + 1, _position.y + direction});
                }
            }
            return possibleMoves;
        }

        char symbol() const override {
            return 'P';
        }
};