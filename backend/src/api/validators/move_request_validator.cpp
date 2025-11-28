#include "api/validators/move_request_validator.hpp"


 Result<MoveRequest> MoveRequestValidator::validate(const MoveRequest& request) {
    if (request.game_id <= 0) {
        return Result<MoveRequest>::failure({"Invalid game_id"});
    }

    if (!SquareValidator::is_valid_square(request.from)) {
        return Result<MoveRequest>::failure({"Invalid from square"});
    }

    if (!SquareValidator::is_valid_square(request.to)) {
        return Result<MoveRequest>::failure({"Invalid to square"});
    }

    if (request.promotion.has_value()) {
        const char promo = request.promotion.value();
        if (promo != 'q' && promo != 'r' && promo != 'b' && promo != 'n') {
            return Result<MoveRequest>::failure({"Invalid promotion"});
        }
    }

    return Result<MoveRequest>::success(request);
}