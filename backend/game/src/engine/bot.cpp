// bot.cpp

#include "engine/bot.hpp"


Bot::Bot(const std::string engine_addr, const int engine_port, int game_id) :
    _engine_addr(engine_addr),
    _engine_port(engine_port),
    _cli(_engine_addr, _engine_port),
    _game_id(game_id)
{
    new_game();
}


void Bot::new_game() {
    std::string cmd = "new_game " + std::to_string(_game_id);
    auto res = _cli.Post("/commands", cmd, "text/plain");
}


void Bot::select_bot() {
    std::string cmd = "select " + std::to_string(_game_id);
    auto res = _cli.Post("/commands", cmd, "text/plain");
}


bool Bot::test_connection() {
    const char *cmd = "uci";
    auto res = _cli.Post("/commands", cmd, "text/plain");
    if (res && res->status==200 && res->body=="uciok") return true;
    else return false;
}


void Bot::set_position(const std::string fen, BBMove move) {
    std::string full_cmd = "position " + fen + UCIParser::bb_to_uci(move).move;
    auto res = _cli.Post("/commands", full_cmd, "text/plain");
}


BBMove Bot::find_best_move() {
    const char *cmd = "go";
    auto res = _cli.Post("/commands", cmd, "text/plain");
    if (res && res->status==200) {
        UCIMove move = {res->body.substr(res->body.size() - 4)};
        std::cout << "Message received : " << res->body << std::endl;
        BBMove bb_move = UCIParser::uci_to_bb(move);
        return bb_move;
    }
}


void Bot::quit() {
    std::string cmd = "quit " + std::to_string(_game_id);
    auto res = _cli.Post("/commands", cmd, "text/plain");
}