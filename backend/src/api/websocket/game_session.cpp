#include "api/websocket/game_session.hpp"


GameSession::GameSession()
: _game(Game()) 
{}


void GameSession::onMoveReceived(crow::websocket::connection& ws, std::string from, std::string to) {

    Parser::ParseResult moveReq = Parser::tryParseMove(from, to);
    if (!moveReq.valid) {
        ws.send_text(moveReq.error);
        return;
    }

    GameBoard& board = _game.getGameBoard();

    bool res = _game.tryApplyMove(moveReq.move);
    if (!res) {
        ws.send_text("Requested move is illegal");
        return;
    }

    _game.nextTurn();

    board.printBoard();

    crow::json::wvalue response;
    GameState game_state = _game.getGameState();
    if (game_state == GameState::CONTINUING) {
        response["type"] = "fen";
        response["fen"] = FEN::toString(_game);
        
    }
    else {
        response["type"] = "endgame";
        response["fen"] = FEN::toString(_game);

        if (game_state == GameState::STALEMATE) response["result"] = "draw";
        else if (_game.getCurrentTurn() == Color::WHITE) {
            response["result"] = "checkmate";
            response["winner"] = "black";
        }
        else {
            response["result"] = "checkmate";
            response["winner"] = "white";      
        }
    }

    std::string s = response.dump();
    ws.send_text(s);
    std::cout << s;
}