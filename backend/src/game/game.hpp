#pragma once

#include "crow.h"

#include "board.hpp"
#include "move_generator.hpp"
#include "pieces/utils/color.hpp"
#include "pieces/utils/position.hpp"


class Game {
    public:

        GameBoard *_board;
        MoveGenerator *_moveGenerator;
        Color _currentTurn = Color::WHITE;
        crow::SimpleApp _app;
        int _blackMoves = 0;
        int _whiteMoves = 0;


        Game(crow::SimpleApp& app) {
            _board = new GameBoard();
            _board->initBoard();
            _moveGenerator = new MoveGenerator(_board);

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

                    Piece *piece = _board->_board[initPos.rank][initPos.file];

                    std::vector<Move> possibleMoves = _moveGenerator->getLegalMoves(_board->_board, initPos);
                    std::vector<Move> legalMoves = _moveGenerator->filterCheckMoves(&piece->_position, possibleMoves);
                    std::vector<Move> withoutCastleMoves = _moveGenerator->filterCastleMoves(&piece->_position, legalMoves);

                    for (Move m: withoutCastleMoves) {
                        if (m.initPos == initPos && m.destPos == destPos) {
                            _board->makeMove(_board->_board, m);
                            _moveGenerator->_history.push_back(m);
                            if (_currentTurn == Color::WHITE) {
                                _whiteMoves++;
                                _currentTurn = Color::BLACK;
                            } 
                            else {
                                _blackMoves++;
                                _currentTurn = Color::WHITE;
                            }
                        }
                    }

                    _board->printBoard(_board->_board);
                    std::cout << toFEN() << std::endl;

                    crow::json::wvalue response;
                    response["type"] = "fen";
                    response["fen"] = toFEN();
                    conn.send_text(response.dump());
                })
                .onclose([this](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
                    CROW_LOG_INFO << "Client disconnected : " << reason;
                });
        }

        std::string toFEN() {
            std::string boardFEN = _board->toFEN();
            if (_currentTurn == Color::WHITE) boardFEN.append(" w ");
            else boardFEN.append(" b ");

            boardFEN.append("KQkq - ");
            boardFEN.append(std::to_string(_blackMoves));
            boardFEN.push_back(' ');
            boardFEN.append(std::to_string(_whiteMoves));
            return boardFEN;
        }

        Position convertInputToPos(std::string pos) {
            Position position;
            int8_t file = pos.at(0) - 'a'; // Convert letter (i.e. 'a') to array indice (i.e. 0)
            int8_t rank = pos.at(1) - '1';
            position = {file, rank};
            return position;
        }

};