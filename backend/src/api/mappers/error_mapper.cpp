#include "api/mappers/error_mapper.hpp"

ErrorResponse ErrorMapper::to_error_response(const GameException& exception) {
    ErrorResponse response;
    response.code = exception.code();
    response.message = exception.what();
    return response;
}