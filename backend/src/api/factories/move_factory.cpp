#include "api/factories/move_factory.hpp"


MoveRequest MoveFactory::from_json(const crow::json::rvalue& json) {
    MoveRequest req;
    req.game_id = json["gameId"].i();
    req.from = json["from"].s();
    req.to = json["to"].s();
    if (json.has("promotion")) {
        req.promotion = json["promotion"].s().begin()[0];
    } else {
        req.promotion = std::nullopt;
    }
    return req;
}