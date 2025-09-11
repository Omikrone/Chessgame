#pragma once

#include "game/pieces/piece.hpp"
#include "game/game_constants.hpp"

#include <vector>
#include <cstdint>


class Pawn : public Piece {

    public:

        Pawn(PieceType pieceType, const Square &startPosition, Color color);

        std::vector<std::vector<Square>> getRawMoves() const override;

        std::unique_ptr<Piece> clone() const;

        char toFEN() const override;
};