#pragma once

#include "api/models/move.hpp"
#include "api/validators/square_validator.hpp"
#include "api/exceptions/game_exception.hpp"


class MoveRequestValidator {
    public:
        static void validate(const MoveRequest& request);
};