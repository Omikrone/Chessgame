#include "api/factories/bb_move_factory.hpp"

int BitboardMoveFactory::square_to_int(const std::string& square) {
    char file = square[0];
    char rank = square[1];

    int file_index = file - 'a';
    int rank_index = rank - '1';

    return rank_index * 8 + file_index;
}

BitboardMove BitboardMoveFactory::from_move_request(const MoveRequest& request) {
    BitboardMove move;
    move.from = square_to_int(request.from);
    move.to = square_to_int(request.to);
    if (!request.promotion.has_value()) {
        return move;
    }
    switch (request.promotion.value()) {
        case 'q':
            move.promotion = PieceType::QUEEN;
            break;
        case 'r':
            move.promotion = PieceType::ROOK;
            break;
        case 'b':
            move.promotion = PieceType::BISHOP;
            break;
        case 'n':
            move.promotion = PieceType::KNIGHT;
            break;
        default:
            break;
    }
    return move;
}
