#include "WebSocketRoutes.hpp"


void registerWebSocketRoutes(crow::App<crow::CORSHandler>& app, GameController& gameController) {
    CROW_WEBSOCKET_ROUTE(app, "/ws/<int>")
        .onopen([](crow::websocket::connection& conn) {
            CROW_LOG_INFO << "Client connected!";
        })
        .onmessage([&gameController](crow::websocket::connection& conn, const std::string& data, bool is_binary){
            crow::json::rvalue body = crow::json::load(data);
            if (!body) {
                return crow::response(400, "Invalid JSON");
            }

            if (!body.has("type")) {
                return crow::response(400, "Missing 'type' field");
            }
            if (!body.has("gameId")) {
                return crow::response(400, "Missing 'gameId' field");
            }
            if (!body.has("from")) {
                return crow::response(400, "Missing 'from' field");
            }
            if (!body.has("to")) {
                return crow::response(400, "Missing 'to' field");
            }

            int gameId = body["gameId"].i();
            std::string from = body["from"].s();
            std::string to = body["to"].s();

            GameSession *session = gameController.getGameSession(gameId);
            if (session == nullptr) {
                std::cout << "no game";
                return crow::response(404, "Requested game not found");
            }
            session->onMoveReceived(conn, from, to);
        })
        .onclose([](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
            CROW_LOG_INFO << "Client disconnected : " << reason;
        });
}
