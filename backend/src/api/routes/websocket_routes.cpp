// websocket_routes.cpp

#include "api/routes/websocket_routes.hpp"


void register_websocket_routes(crow::App<crow::CORSHandler>& app, GameController& gameController) {

    // Creates a new websocket route
    CROW_WEBSOCKET_ROUTE(app, "/ws/<int>")
        .onopen([](crow::websocket::connection& /*conn*/) {
            CROW_LOG_INFO << "Client connected!";
        })
        .onmessage([&gameController](crow::websocket::connection& conn, const std::string& data, bool /*is_binary*/){
            std::cout << "received" << std::endl;
            try {

                // Parses the data received to a rvalue
                crow::json::rvalue body;
                crow::json::load(data);

                // Validates the different fields of the message
                MoveJsonValidator::validate(body);

                MoveRequest move = MoveFactory::from_json(body);

                // Searches for the corresponding game
                uint64_t game_id = move.game_id;
                GameSession* session = gameController.get_game_session(game_id);

                // Validates the move request
                MoveRequestValidator::validate(move);

                BitboardMove bb_move = BitboardMoveFactory::from_move_request(move);

                session->on_move_received(conn, bb_move);
                
            } catch (const GameException& e) {
                ErrorResponse error = ErrorMapper::to_error_response(e);
                conn.send_text(error.to_json().dump());
            } catch (const std::exception& e) {
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
