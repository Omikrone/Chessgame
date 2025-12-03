// game_session.cpp

#include "api/websocket/game_session.hpp"

const char* host_env = std::getenv("ENGINE_HOST");
const char* port_env = std::getenv("ENGINE_PORT");

std::string host = host_env ? std::string(host_env) : std::string("127.0.0.1");
std::string port = port_env ? std::string(port_env) : std::string("18088");

GameSession::GameSession(const int id)
    : _id(id), _game(Game()), _engine(host, std::stoi(port), id), _last_activity(std::chrono::steady_clock::now()) {
    std::cout << "Created game session with ID " << _id << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    _player_color = dis(gen) == 0 ? Color::WHITE : Color::BLACK;
    std::cout << "Player color : " << (_player_color == Color::WHITE ? "white" : "black") << std::endl;
}

GameSession::~GameSession() { _engine.quit(); }

void GameSession::apply_engine_move(crow::websocket::connection& ws) {
    _engine.update_position(true, "startpos", _game.get_played_moves());

    Move best_move = _engine.find_best_move();
    std::cout << "FEN before bot move : " << _game.get_fen() << std::endl;
    bool res = _game.try_apply_move(best_move.from, best_move.to);
    if (!res) {
        throw GameException("Engine played illegal move", 500);
    }

    std::cout << "FEN after bot move : " << _game.get_fen() << std::endl;
    _game.next_turn();

    GameState state = _game.get_game_state();
    PositionResponse game_state =
        PositionMapper::to_position_response(state, _game.get_fen(), _game.get_current_turn());
    std::string s = game_state.to_json().dump();
    ws.send_text(s);
}

void GameSession::apply_player_move(crow::websocket::connection& ws, BitboardMove move) {
    bool res = _game.try_apply_move(move.from, move.to, move.promotion);
    if (!res) {
        throw GameException("Illegal move", 400);
    }
    _game.next_turn();

    GameState state = _game.get_game_state();
    PositionResponse position_response =
        PositionMapper::to_position_response(state, _game.get_fen(), _game.get_current_turn());
    crow::json::wvalue game_state1 = position_response.to_json();
    std::string s = game_state1.dump();
    ws.send_text(s);
}

void GameSession::on_move_received(crow::websocket::connection& ws, BitboardMove move) {
    reset_idle();

    apply_player_move(ws, move);
    GameState state = _game.get_game_state();
    if (state != GameState::CONTINUING) return;
    apply_engine_move(ws);
}

bool GameSession::is_idle() const {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = now - _last_activity;
    return elapsed > std::chrono::minutes(30);
}

void GameSession::reset_idle() { _last_activity = std::chrono::steady_clock::now(); }

Color GameSession::get_player_color() const { return _player_color; }

int GameSession::get_id() const { return _id; }