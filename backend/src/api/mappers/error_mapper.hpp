#pragma once

#include "api/models/error.hpp"
#include "api/exceptions/game_exception.hpp"


class ErrorMapper {
    public:
        static ErrorResponse to_error_response(const GameException& exception) {
            ErrorResponse response;
            response.code = exception.code();
            response.message = exception.what();
            return response;
        }
};