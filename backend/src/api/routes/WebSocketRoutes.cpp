#include "WebSocketRoutes.hpp"


void registerWebSocketRoutes(crow::App<crow::CORSHandler>& app, GameController& gameController) {
    CROW_WEBSOCKET_ROUTE(app, "/ws/<int>")
        .onopen([](crow::websocket::connection& conn) {
            CROW_LOG_INFO << "Client connected!";
        })
        .onmessage([&gameController](crow::websocket::connection& conn, const std::string& data, bool is_binary){
            crow::json::rvalue body = crow::json::load(data);
            if (!body) {
                conn.send_text("Invalid JSON");
            }

            if (!body.has("type")) {
                conn.send_text("Missing 'type' field");
            }
            if (!body.has("gameId")) {
                conn.send_text("Missing 'gameId' field");
            }
            if (!body.has("from")) {
                conn.send_text("Missing 'from' field");
            }
            if (!body.has("to")) {
                conn.send_text("Missing 'to' field");
            }

            int gameId = body["gameId"].i();
            std::string from = body["from"].s();
            std::string to = body["to"].s();

            GameSession *session = gameController.getGameSession(gameId);
            if (session == nullptr) {
                conn.send_text("Requested game not found");
            }
            session->onMoveReceived(conn, from, to);
        })
        .onclose([](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
            CROW_LOG_INFO << "Client disconnected : " << reason;
        });
}
