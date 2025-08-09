#pragma once

#include "crow.h"

#include "board.hpp"
#include "pieces/color.hpp"
#include "pieces/position.hpp"


class Game {
    public:

        GameBoard *_board;
        Color _currentTurn;


        Game(crow::SimpleApp& app) {
            _board = new GameBoard();
            _board->initBoard();

            CROW_WEBSOCKET_ROUTE(app, "/ws")
                .onopen([this](crow::websocket::connection& conn) {
                    CROW_LOG_INFO << "Client connected!";
                })
                .onmessage([this](crow::websocket::connection& conn, const std::string& data, bool is_binary){
                    CROW_LOG_INFO << "New message : " << data;
                })
                .onclose([this](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
                    CROW_LOG_INFO << "Client disconnected : " << reason;
                });
        }


        void start() {
            
            Position initPos, destPos;

            while (true) {
                _board->printBoard();

                Position initPos = getUserInput("Enter the coordinates of the piece you want to play (col,row) : ");

                std::vector<Position> moves = _board->getLegalMoves(initPos);
                std::vector<Position> legalMoves = _board->filterCheckMoves(&initPos, moves);

                destPos = getUserInput("Enter the destination of the piece (col,row) : ");

                if(std::find(legalMoves.begin(), legalMoves.end(), destPos) != legalMoves.end()) {
                    _board->makeMove(initPos, destPos);
                } else {
                    std::cout << "This move is not allowed !";
                }
            }
        }

        bool isGameOver() {

        }

        Position getUserInput(std::string text) {
            std::string input;
            Position position;
            std::cout << text;
            std::cin >> input;
            position = {static_cast<signed char>(input.at(0) - '0'), static_cast<signed char>(input[2] - '0')};
            return position;
        }

};