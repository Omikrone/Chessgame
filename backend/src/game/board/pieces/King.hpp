#pragma once

#include "piece.hpp"
#include "utils/constants.hpp"

#include <vector>
#include <cstdint>


class King: public Piece {

    public:
        King(Type pieceType, const Square &startPosition, Color color);

        std::vector<std::vector<Square>> getRawMoves() const override;

        std::unique_ptr<Piece> clone() const override;

        char toFEN() const override;

};