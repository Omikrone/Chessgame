#include "api/routes/game_routes.hpp"


void registerGameRoutes(crow::App<crow::CORSHandler>& app, GameController &gameController) {
    
    CROW_ROUTE(app, "/games").methods("POST"_method)
    ([&app, &gameController](const crow::request& req){
        int gameId = gameController.createGame();

        crow::json::wvalue res;
        res["status"] = "success";
        res["gameId"] = gameId;
        return crow::response(200, res);
    });
}