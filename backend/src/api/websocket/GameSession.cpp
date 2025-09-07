#include "GameSession.hpp"


GameSession::GameSession()
: _game(Game()) 
{}


void GameSession::onMoveReceived(crow::websocket::connection& ws, std::string from, std::string to) {

    Move moveReq = Parser::parseMove(from, to);

    GameBoard& board = _game.getGameBoard();
    board.printBoard();
    std::vector<Move> possibleMoves = _game.getLegalMoves(moveReq.initPos);
    for (Move m: possibleMoves) {
        if (m == moveReq) {
            _game.applyMove(m);
        }
    }
    board.printBoard();

    crow::json::wvalue response;
    response["type"] = "fen";
    response["fen"] = FEN::toString(_game);

    std::string s = response.dump();
    ws.send_text(s);
    std::cout << s;
}