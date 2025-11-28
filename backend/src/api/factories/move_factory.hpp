#pragma once

#include "api/models/move.hpp"


class MoveFactory {

    public:
        static MoveRequest from_json(const crow::json::rvalue& json);
};