#pragma once

#include "piece.hpp"
#include "utils/constants.hpp"

#include <vector>
#include <cstdint>


class Rook: public Piece {

    public:
        Rook(Type pieceType, const Square &startPosition, Color color);

        std::vector<std::vector<Square>> getRawMoves() const override;

        static std::vector<std::vector<Square>> getRookMoves(const Square &currentPosition);

        std::unique_ptr<Piece> clone() const override;
        
        char toFEN() const override;
};