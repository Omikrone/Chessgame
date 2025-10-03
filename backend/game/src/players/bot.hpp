// bot.hpp

#pragma once

#include "uci_parser.hpp"

#include <string>
#include <vector>
#include "httplib.h"


class Bot
{

    private:

        const std::string _engine_addr;
        const int _engine_port;
        httplib::Client _cli;

    public:

        Bot(const std::string engine_addr, const int engine_port);
        ~Bot() = default;

        bool test_connection();
        void new_game();
        void set_position(const std::string fen, BBMove played_move);
        BBMove find_best_move();
};