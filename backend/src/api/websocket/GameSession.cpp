#include "GameSession.hpp"


GameSession::GameSession()
: _game(Game()) 
{}


void GameSession::onMoveReceived(std::string rawMove) {
                
    std::string from = rawMove["from"].s();
    std::string to = rawMove["to"].s();
    Move moveReq = Parser::parseMove(from, to);
    CROW_LOG_INFO << "New message : " << rawMove;

    std::vector<Move> possibleMoves = _game.getLegalMoves(moveReq.initPos);
    for (Move m: possibleMoves) {
        if (m == moveReq) {
            _game.applyMove(m);
        }
    }

    GameBoard& board = _game.getGameBoard();
    board.printBoard();

    crow::json::wvalue response;
    response["type"] = "fen";
    response["fen"] = FEN::toString(_game);

    _ws->send_text(response.dump());
}