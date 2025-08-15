#pragma once

#include "piece.hpp"
#include "utils/constants.hpp"
#include "utils/type.hpp"

#include <vector>
#include <cstdint>


class Pawn : public Piece {

    public:

        Pawn(Type pieceType, const Square &startPosition, Color color)
            : Piece(pieceType, startPosition, color) {}

        std::vector<std::vector<Square>> getRawMoves() const override {
            std::vector<std::vector<Square>> possibleMoves;

            std::int8_t direction = static_cast<std::int8_t>(_color);

            if (_position.rank + direction >= 0 && _position.rank + direction < BOARD_LENGTH) {

                std::vector<Square> directionMoves;

                // Forward walk
                directionMoves.push_back({_position.file, _position.rank + direction});
                if (_color == Color::WHITE && _position.rank == 1 ||
                    _color == Color::BLACK && _position.rank == 6) {
                        directionMoves.push_back({_position.file, _position.rank + direction * 2});
                    }
                possibleMoves.push_back(directionMoves);

                if (_position.file > 0) {
                    directionMoves.clear();
                    // First side capture
                    directionMoves.push_back({_position.file - 1, _position.rank + direction});
                    possibleMoves.push_back(directionMoves);
                }
                if (_position.file < BOARD_LENGTH - 1) {
                    directionMoves.clear();
                    // Second side capture
                    directionMoves.push_back({_position.file + 1, _position.rank + direction});
                    possibleMoves.push_back(directionMoves);
                }
            }
            return possibleMoves;
        }

        Piece* clone() const override {
            return new Pawn(*this);
        }

        char toFEN() const override {
            if (_color == Color::WHITE) return 'P';
            else return 'p';
        }
};