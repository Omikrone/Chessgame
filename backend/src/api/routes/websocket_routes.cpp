// websocket_routes.cpp

#include "api/routes/websocket_routes.hpp"


void register_websocket_routes(crow::App<crow::CORSHandler>& app, GameController& gameController) {

    // Creates a new websocket route
    CROW_WEBSOCKET_ROUTE(app, "/ws/<int>")
        .onopen([](crow::websocket::connection& /*conn*/) {
            CROW_LOG_INFO << "Client connected!";
        })
        .onmessage([&gameController](crow::websocket::connection& conn, const std::string& data, bool /*is_binary*/){
            std::cout << "received : " << data << std::endl;
            try {

                // Parses the data received to a rvalue
                crow::json::rvalue body = crow::json::load(data);

                // Validates the different fields of the message
                JsonValidator::validate(body);

                if (body["msgType"].s() == "init") {
                    // Initialization message
                    int game_id = body["gameId"].i();
                    GameSession* session = gameController.get_game_session(game_id);

                    if (session->get_player_color() == Color::BLACK) {
                        // If the player is black, engine plays first move
                        session->apply_engine_move(conn);
                        return;
                    }
                }
                
                if (body["msgType"].s() == "move") {
                    MoveRequest move = MoveFactory::from_json(body);

                    // Searches for the corresponding game
                    uint64_t game_id = move.game_id;
                    GameSession* session = gameController.get_game_session(game_id);

                    // Validates the move request
                    MoveRequestValidator::validate(move);

                    BitboardMove bb_move = BitboardMoveFactory::from_move_request(move);

                    session->on_move_received(conn, bb_move);
                }
            } catch (const GameException& e) {
                ErrorResponse error = ErrorMapper::to_error_response(e);
                conn.send_text(error.to_json().dump());
            } catch (const std::exception& e) {
                std::cout << "Internal server error: " << e.what() << std::endl;
                ErrorResponse error;
                error.code = 500;
                error.message = "Internal server error";
                conn.send_text(error.to_json().dump());
            }
        })
        .onclose([&gameController](crow::websocket::connection& conn, const std::string& reason) {
            gameController.remove_idle_games();
            CROW_LOG_INFO << "Client disconnected : " << reason;
        });
}
