#include "GameSession.hpp"


GameSession::GameSession()
: _game(Game()) 
{}


void GameSession::onMoveReceived(crow::websocket::connection& ws, std::string from, std::string to) {

    Move moveReq = Parser::parseMove(from, to);

    GameBoard& board = _game.getGameBoard();
    board.printBoard();
    std::vector<Move> possibleMoves = _game.getLegalMoves(moveReq.initPos);
    std::cout << "all good";
    for (Move m: possibleMoves) {
        if (m == moveReq) {
            _game.applyMove(m);
        }
    }
    board.printBoard();

    std::cout << "CACA2";

    crow::json::wvalue response;
    response["type"] = "fen";
    response["fen"] = FEN::toString(_game);

    ws.send_text(response.dump());
    std::cout << response.dump();
}