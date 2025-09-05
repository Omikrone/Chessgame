#include "GameRoutes.hpp"


void registerGameRoutes(crow::SimpleApp& app, GameController &gameController) {
    
    CROW_ROUTE(app, "/games").methods("POST"_method)
    ([&app, &gameController](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "Invalid JSON");

        int gameId = gameController.createGame();

        crow::json::wvalue res;
        res["status"] = "success";
        res["gameId"] = gameId;
        return crow::response(200, res);
    });
}