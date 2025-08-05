#pragma once

#include "piece.hpp"
#include "../board.hpp"

#include <vector>
#include <list>


class Pawn : public Piece {

    public:

        Pawn(const Position &startPosition, Color color)
            : Piece(startPosition, color) {}

        std::vector<Position> getPossibleMoves() const override {
            std::vector<Position> possibleMoves;

            signed char direction = static_cast<signed char>(_color);

            if (_position.y + direction >= 0 && _position.y + direction < BOARD_LENGTH) {

                // Forward walk
                possibleMoves.push_back({_position.x, _position.y + _position.y + direction});

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