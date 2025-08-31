
#include "WebSocketRoutes.hpp"


void registerWebSocketRoutes(crow::SimpleApp& app, GameController& gameController) {
    CROW_WEBSOCKET_ROUTE(app, "/ws/<int>")
        .onopen([this](crow::websocket::connection& conn) {
            CROW_LOG_INFO << "Client connected!";
        })
        .onmessage([&gameController](crow::websocket::connection& conn, const std::string& data, bool is_binary){
            crow::json::rvalue body = crow::json::load(data);
            int gameId = body["msg"].i();
            GameSession session = gameController.getSession(gameId);
            session.onMoveReceived(body);

        })
        .onclose([this](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
            CROW_LOG_INFO << "Client disconnected : " << reason;
        });
}
