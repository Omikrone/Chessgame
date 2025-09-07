#include "GameSession.hpp"


GameSession::GameSession()
: _game(Game()) 
{}


void GameSession::onMoveReceived(crow::websocket::connection& ws, std::string from, std::string to) {

    Move moveReq = Parser::parseMove(from, to);

    GameBoard& board = _game.getGameBoard();
    board.printBoard();
    bool res = _game.applyMove(moveReq);
    if (res) _game.nextTurn();

    board.printBoard();

    crow::json::wvalue response;
    response["type"] = "fen";
    response["fen"] = FEN::toString(_game);

    std::string s = response.dump();
    ws.send_text(s);
    std::cout << s;
}