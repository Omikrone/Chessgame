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
    move.promotion = request.promotion;
    return move;
}

    