#include "api/routes/game_routes.hpp"


void register_game_routes(crow::App<crow::CORSHandler>& app, GameController &gameController) {
    
    CROW_ROUTE(app, "/games").methods("POST"_method)
    ([&app, &gameController](const crow::request& /*req*/){
        uint64_t gameId = gameController.create_game();

        crow::json::wvalue res;
        res["status"] = "success";
        res["gameId"] = gameId;
        return crow::response(200, res);
    });
}