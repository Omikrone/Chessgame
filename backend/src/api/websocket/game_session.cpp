#include "api/websocket/game_session.hpp"


GameSession::GameSession()
: _game(Game()) 
{}


void GameSession::on_move_received(crow::websocket::connection& ws, std::string from, std::string to) {

    Parser::ParseResult moveReq = Parser::try_parse_move(from, to);
    if (!moveReq.valid) {
        ws.send_text(moveReq.error);
        return;
    }

    GameBoard& board = _game.get_game_board();

    bool res = _game.try_apply_move(moveReq.move);
    if (!res) {
        ws.send_text("Requested move is illegal");
        return;
    }

    _game.next_turn();

    board.print_board();

    crow::json::wvalue response;
    GameState game_state = _game.get_game_state();
    if (game_state == GameState::CONTINUING) {
        response["type"] = "fen";
        response["fen"] = FEN::to_string(_game);
        
    }
    else {
        response["type"] = "endgame";
        response["fen"] = FEN::to_string(_game);

        if (game_state == GameState::STALEMATE) response["result"] = "draw";
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
    std::cout << s;
}