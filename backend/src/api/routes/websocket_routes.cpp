// websocket_routes.cpp

#include "api/routes/websocket_routes.hpp"


void register_websocket_routes(crow::App<crow::CORSHandler>& app, GameController& gameController) {

    // Creates a new websocket route
    CROW_WEBSOCKET_ROUTE(app, "/ws/<int>")
        .onopen([](crow::websocket::connection& /*conn*/) {
            CROW_LOG_INFO << "Client connected!";
        })
        .onmessage([&gameController](crow::websocket::connection& conn, const std::string& data, bool /*is_binary*/){

            // Parses the data received to a rvalue
            crow::json::rvalue body = crow::json::load(data);

            // Validates the different fields of the message
            DataValidator::Result result = DataValidator::is_message_valid(body);
            if (!result.valid) {
                conn.send_text(result.error);
                return;
            }

            // Searches for trhe corresponding game
            uint64_t gameId = body["gameId"].u();
            GameSession *session = gameController.get_game_session(gameId);
            if (session == nullptr) {
                conn.send_text("Requested game not found");
                return;
            }

            // Sends the move to the session
            std::string from = body["from"].s();
            std::string to = body["to"].s();
            session->on_move_received(conn, from, to);
        })
        .onclose([](crow::websocket::connection& /*conn*/, const std::string& reason, uint16_t) {
            CROW_LOG_INFO << "Client disconnected : " << reason;
        });
}
