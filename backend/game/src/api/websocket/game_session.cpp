// game_session.cpp

#include "api/websocket/game_session.hpp"

const char* host_env = std::getenv("ENGINE_HOST");
const char* port_env = std::getenv("ENGINE_PORT");

std::string host = host_env ? std::string(host_env) : std::string("127.0.0.1");
std::string port = port_env ? std::string(port_env) : std::string("18088");

GameSession::GameSession(const int id)
: _id(id), _game(Game()), _bot(host, std::stoi(port), id), _last_activity(std::chrono::steady_clock::now())
{}

GameSession::~GameSession() {
    _bot.quit();
}


void GameSession::on_move_received(crow::websocket::connection& ws, std::string from, std::string to) {
    reset_idle();

    // Tries to parse the positions sent by the client
    Parser::ParseIntResult moveReq = Parser::move_to_int(from, to);
    if (!moveReq.valid) {
        ws.send_text(moveReq.error);
        return;
    }

    // Tries to apply the move on the game board
    bool res = _game.try_apply_move(moveReq.from, moveReq.to);
    if (!res) {
        ws.send_text("Illegal move");
        return;
    }

    GameState state = _game.get_game_state();
    send_game_state(ws, state);
    if (state != GameState::CONTINUING) return;

    _engine.update_position(_id, _game.get_fen(), {moveReq.from, moveReq.to});

    send_bot_move(ws);
}


void GameSession::send_bot_move(crow::websocket::connection& ws) {
    
    BBMove best_move = _bot.find_best_move();
    std::cout << "FEN before bot move : " << _game.get_fen() << std::endl;
    bool res = _game.try_apply_move(best_move.from, best_move.to);
    if (!res) std::cout << "ILLEGAL MOVE" << std::endl;
    std::cout << "FEN after bot move : " << _game.get_fen() << std::endl;
    _game.next_turn();
    send_game_state(ws, _game.get_game_state());
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

bool GameSession::is_idle() const {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = now - _last_activity;
    return elapsed > std::chrono::minutes(30);
}


void GameSession::reset_idle() {
    _last_activity = std::chrono::steady_clock::now();
}