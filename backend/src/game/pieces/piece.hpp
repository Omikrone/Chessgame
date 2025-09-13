#pragma once

#include <vector>

#include "game/game_constants.hpp"
#include "game/components/square.hpp"
#include "game/components/move.hpp"


class Piece {
public:

    PieceType _pieceType;
    Square _position;
    Color _color;
    bool _hasMoved = false;

    Piece(PieceType pieceType, const Square& position, Color color)
        : _pieceType(pieceType), _position(position), _color(color) {}

    virtual std::unique_ptr<Piece> clone() const = 0;

    virtual ~Piece() = default;

    virtual char to_fen() const = 0;
    virtual std::vector<std::vector<Square>> get_raw_moves() const = 0;
};