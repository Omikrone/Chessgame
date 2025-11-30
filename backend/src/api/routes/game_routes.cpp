// game_routes.cpp

#include "api/routes/game_routes.hpp"


void register_game_routes(crow::App<crow::CORSHandler>& app, GameController& gameController) {
    
    // Creates a new POST route for creating new games
    CROW_ROUTE(app, "/games").methods("POST"_method)
    ([&app, &gameController](const crow::request& /*req*/){

        // Creates a new game
        GameSession* game = gameController.create_game();

        // Replies by sending the game ID to the client
        crow::json::wvalue res;
        res["status"] = "success";
        res["gameId"] = game->get_id();
        if (game->get_player_color() == Color::WHITE) {
            res["playerColor"] = "white";
        } else {
            res["playerColor"] = "black";
        }
        return crow::response(200, res);
    });
}