// game_session.cpp

#include "api/websocket/game_session.hpp"


const char* host_env = std::getenv("ENGINE_HOST");
const char* port_env = std::getenv("ENGINE_PORT");

std::string host = host_env ? std::string(host_env) : std::string("127.0.0.1");
std::string port = port_env ? std::string(port_env) : std::string("18088");


GameSession::GameSession(const int id)
: _id(id), _game(Game()), _engine(host, std::stoi(port), id), _last_activity(std::chrono::steady_clock::now())
{}

GameSession::~GameSession() {
    _engine.quit();
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
    crow::json::wvalue game_state1 = ResponseParser::parse_game_state(state, _game.get_fen(), _game.get_current_turn());
    std::string s = game_state1.dump();
    ws.send_text(s);
    if (state != GameState::CONTINUING) return;

    _engine.update_position(_id, _game.get_fen(), _game.get_played_moves());

    Move best_move = _engine.find_best_move(_id);
    std::cout << "FEN before bot move : " << _game.get_fen() << std::endl;
    res = _game.try_apply_move(best_move.from, best_move.to);
    if (!res) std::cout << "ILLEGAL MOVE" << std::endl;
    std::cout << "FEN after bot move : " << _game.get_fen() << std::endl;
    _game.next_turn();

    crow::json::wvalue game_state2 = ResponseParser::parse_game_state(_game.get_game_state(), _game.get_fen(), _game.get_current_turn());
    s = game_state2.dump();
    ws.send_text(s);
}


bool GameSession::is_idle() const {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = now - _last_activity;
    return elapsed > std::chrono::minutes(30);
}


void GameSession::reset_idle() {
    _last_activity = std::chrono::steady_clock::now();
}