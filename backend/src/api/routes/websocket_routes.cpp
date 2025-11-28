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

            // Parses the data received to a rvalue
            crow::json::rvalue body = crow::json::load(data);

            // Validates the different fields of the message
            Result<crow::json::rvalue> validationResult = MoveJsonValidator::validate(body);
            if (!validationResult.ok) {
                conn.send_text(validationResult.errors.value()[0]);
                return;
            }

            MoveRequest move = MoveFactory::from_json(body);

            // Searches for the corresponding game
            uint64_t game_id = move.game_id;
            GameSession *session = gameController.get_game_session(game_id);
            if (session == nullptr) {
                conn.send_text("Requested game not found");
                return;
            }

            // Validates the move request
            Result<MoveRequest> moveValidationResult = MoveRequestValidator::validate(move);
            if (!moveValidationResult.ok) {
                conn.send_text(moveValidationResult.errors.value()[0]);
                return;
            }

            BitboardMove bb_move = BitboardMoveFactory::from_move_request(move);

            session->on_move_received(conn, bb_move);
        })
        .onclose([&gameController](crow::websocket::connection& conn, const std::string& reason) {
            gameController.remove_idle_games();
            CROW_LOG_INFO << "Client disconnected : " << reason;
        });
}
