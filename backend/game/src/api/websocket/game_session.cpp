// game_session.cpp

#include "api/websocket/game_session.hpp"


GameSession::GameSession()
: _game(Game()) 
{}


void GameSession::on_move_received(crow::websocket::connection& ws, std::string from, std::string to) {

    // Tries to parse the positions sent by the client
    Parser::ParseResult moveReq = Parser::try_parse_move(from, to);
    if (!moveReq.valid) {
        ws.send_text(moveReq.error);
        return;
    }

    // Tries to apply the move on the game board
    bool res = _game.try_apply_move(moveReq.from, moveReq.to);

    EndGame game_state;
    if (res) {
        _game.next_turn();
        game_state = _game.get_game_state();
    }
    else game_state = EndGame::CONTINUING;

    // Replies to the client by sending him the game state
    crow::json::wvalue response;
   
    if (game_state == EndGame::CONTINUING) {
        response["type"] = "fen";
        response["fen"] = _game.get_fen();
    }
    else {
        response["type"] = "endgame";
        response["fen"] = _game.get_fen();

        if (game_state == EndGame::STALEMATE) response["result"] = "draw";
        else if (_game.get_current_turn() == Color::WHITE) {
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
}