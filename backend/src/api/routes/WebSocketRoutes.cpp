
#include "WebSocketRoutes.hpp"


void registerWebSocketRoutes(crow::SimpleApp& app, GameController& gameController) {
    CROW_WEBSOCKET_ROUTE(app, "/ws/<int>")
        .onopen([this](crow::websocket::connection& conn) {
            CROW_LOG_INFO << "Client connected!";
        })
        .onmessage([this](crow::websocket::connection& conn, const std::string& data, bool is_binary){
            crow::json::rvalue body = crow::json::load(data);
            std::string from = body["from"].s();
            std::string to = body["to"].s();
            Square initPos = convertInputToPos(from);
            Square destPos = convertInputToPos(to);
            CROW_LOG_INFO << "New message : " << data;

            std::vector<Move> possibleMoves = _moveGenerator->getPossibleMoves(_board->_board, initPos);

            _board->printBoard(_board->_board);

            crow::json::wvalue response;
            response["type"] = "fen";
            response["fen"] = toFEN();

            conn.send_text(response.dump());
            
            GameState state = checkEndGame();
            crow::json::wvalue endGameRes;
        })
        .onclose([this](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
            CROW_LOG_INFO << "Client disconnected : " << reason;
        });
}
