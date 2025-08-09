#pragma once

#include "crow.h"

#include "board.hpp"
#include "pieces/color.hpp"
#include "pieces/position.hpp"


class Game {
    public:

        GameBoard *_board;
        Color _currentTurn;
        crow::SimpleApp _app;


        Game(crow::SimpleApp& app) {
            _board = new GameBoard();
            _board->initBoard();

            CROW_WEBSOCKET_ROUTE(app, "/ws")
                .onopen([this](crow::websocket::connection& conn) {
                    CROW_LOG_INFO << "Client connected!";
                })
                .onmessage([this](crow::websocket::connection& conn, const std::string& data, bool is_binary){
                    crow::json::rvalue body = crow::json::load(data);
                    std::string from = body["from"].s();
                    std::string to = body["to"].s();
                    Position initPos = convertInputToPos(from);
                    Position destPos = convertInputToPos(to);
                    CROW_LOG_INFO << "New message : " << data;

                    std::vector<Position> moves = _board->getLegalMoves(initPos);
                    std::vector<Position> legalMoves = _board->filterCheckMoves(&initPos, moves);

                    if(std::find(legalMoves.begin(), legalMoves.end(), destPos) != legalMoves.end()) {
                        _board->makeMove(initPos, destPos);
                    } else {
                        std::cout << "This move is not allowed !";
                    }
                    _board->printBoard();
                })
                .onclose([this](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
                    CROW_LOG_INFO << "Client disconnected : " << reason;
                });
        }


        void start() {
            
            Position initPos, destPos;

            while (true) {

            }
        }

        bool isGameOver() {

        }

        Position convertInputToPos(std::string pos) {
            Position position;
            int8_t file = pos.at(0) - 'a'; // Convert letter (i.e. 'a') to array indice (i.e. 0)
            int8_t rank = pos.at(1) - '1';
            position = {file, rank};
            return position;
        }

};