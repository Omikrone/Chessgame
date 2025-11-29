#include "api/validators/move_request_validator.hpp"


 void MoveRequestValidator::validate(const MoveRequest& request) {
    if (request.game_id <= 0) {
        throw GameException("Invalid game_id", 400);
    }

    if (!SquareValidator::is_valid_square(request.from)) {
        throw GameException("Invalid from square", 400);
    }

    if (!SquareValidator::is_valid_square(request.to)) {
        throw GameException("Invalid to square", 400);
    }

    if (request.promotion.has_value()) {
        const char promo = request.promotion.value();
        if (promo != 'q' && promo != 'r' && promo != 'b' && promo != 'n') {
            throw GameException("Invalid promotion", 400);
        }
    }
}