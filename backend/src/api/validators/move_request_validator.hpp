#pragma once

#include "api/models/move.hpp"
#include "api/validators/square_validator.hpp"
#include "api/validators/result.hpp"


class MoveRequestValidator {
    public:
        static Result<MoveRequest> validate(const MoveRequest& request);
};