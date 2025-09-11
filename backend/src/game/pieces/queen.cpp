#include "game/pieces/queen.hpp"


Queen::Queen(PieceType pieceType, const Square &startPosition, Color color)
    : Piece(pieceType, startPosition, color) {}

std::vector<std::vector<Square>> Queen::getRawMoves() const {
    std::vector<std::vector<Square>> possibleMoves = Bishop::getBishopMoves(_position);
    std::vector<std::vector<Square>> rookMoves = Rook::getRookMoves(_position);

    possibleMoves.insert(possibleMoves.end(), rookMoves.begin(), rookMoves.end());
    return possibleMoves;
}

std::unique_ptr<Piece> Queen::clone() const {
    return std::make_unique<Queen>(*this);
}

char Queen::toFEN() const {
    if (_color == Color::WHITE) return 'Q';
    else return 'q';
}