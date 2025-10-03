// game_session.cpp

#include "api/websocket/game_session.hpp"


GameSession::GameSession()
: _game(Game()), _bot("127.0.0.1", 18088)
{}


void GameSession::on_move_received(crow::websocket::connection& ws, std::string from, std::string to) {
    std::cout << "MESSAGE RECEIVED" << std::endl;

    // Tries to parse the positions sent by the client
    Parser::ParseIntResult moveReq = Parser::move_to_int(from, to);
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

    send_game_state(ws, game_state);
    update_bot_position({moveReq.from, moveReq.to});
}


void GameSession::send_bot_move(crow::websocket::connection& ws) {
    
    BBMove best_move = _bot.find_best_move();
    std::cout << "BEST MOVES ?: " << best_move.from << best_move.to << std::endl;
    bool res = _game.try_apply_move(best_move.from, best_move.to);
    if (res) std::cout << "LEGAL MOVE" << std::endl;
    _game.next_turn();
    send_game_state(ws, _game.get_game_state());
    std::cout << "All moves sent" << std::endl;
}

void GameSession::update_bot_position(BBMove bb_move) {
    _bot.set_position("startpos", bb_move);
}


void GameSession::send_game_state(crow::websocket::connection& ws, EndGame game_state) {
    

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
    std::cout << "Sendin game state" << std::endl;
}