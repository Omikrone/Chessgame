#pragma once

#include "api/models/move.hpp"

#include "game/game_constants.hpp"


class BitboardMoveFactory {
    private:
        static int square_to_int(const std::string& square);

    public:
        static BitboardMove from_move_request(const MoveRequest& request);
};