#include "api/validators/move_factory.hpp"


MoveRequest MoveFactory::from_json(const crow::json::rvalue& json) {
    MoveRequest req;
    req.game_id = json["game_id"].i();
    req.from = json["from"].s();
    req.to = json["to"].s();
    if (json.has("promotion")) {
        req.promotion = json["promotion"].s();
    } else {
        req.promotion = std::nullopt;
    }
    return req;
}