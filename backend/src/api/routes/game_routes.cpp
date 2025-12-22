// game_routes.cpp

#include "api/routes/game_routes.hpp"

void register_game_routes(crow::App<crow::CORSHandler>& app, GameController& game_controller) {
    // Creates a new POST route for creating new games
    CROW_ROUTE(app, "/games").methods("POST"_method)([&game_controller](const crow::request& /*req*/) {
        // Creates a new game
        GameSession* game = game_controller.create_game();

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

    CROW_ROUTE(app, "/games/<int>").methods("GET"_method)([&game_controller](const crow::request& /*req*/, int game_id) {

        GameSession* game = game_controller.get_game_session(game_id);
        if (game == nullptr) {
            crow::json::wvalue res;
            res["status"] = "error";
            res["message"] = "No active game session found";
            return crow::response(404, res);
        }

        crow::json::wvalue res;
        res["status"] = "success";
        res["gameId"] = game->get_id();
        if (game->get_player_color() == Color::WHITE) {
            res["playerColor"] = "white";
        } else {
            res["playerColor"] = "black";
        }
        res["fen"] = game->get_board_fen();
        return crow::response(200, res);
    });
}