#pragma once

#include "piece.hpp"
#include "rook.hpp"
#include "bishop.hpp"
#include "utils/constants.hpp"

#include <vector>
#include <cstdint>


class Queen: public Piece {

    public:
        Queen(Type pieceType, const Square &startPosition, Color color);

        std::vector<std::vector<Square>> getRawMoves() const override;

        std::unique_ptr<Piece> clone() const override;

        char toFEN() const override;
};