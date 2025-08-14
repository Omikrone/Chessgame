#pragma once

#include "crow.h"

#include "board.hpp"
#include "move_generator.hpp"
#include "pieces/utils/color.hpp"
#include "pieces/utils/position.hpp"
#include "pieces/utils/game_state.hpp"


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

                    std::vector<Move> possibleMoves = _moveGenerator->getPossibleMoves(_board->_board, initPos);

                    if (_board->_board[initPos.rank][initPos.file] != nullptr && _board->_board[initPos.rank][initPos.file]->_color == _currentTurn) {
                        for (Move m: possibleMoves) {
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
                    }

                    _board->printBoard(_board->_board);
                    std::cout << toFEN() << std::endl;

                    crow::json::wvalue response;
                    response["type"] = "fen";
                    response["fen"] = toFEN();

                    conn.send_text(response.dump());
                    
                    GameState state = checkEndGame();
                    crow::json::wvalue endGameRes;

                    if (state == GameState::CHECKMATE) {
                        endGameRes["type"] = "endgame";
                        endGameRes["game_state"] = "checkmate";
                        if (_currentTurn == Color::BLACK) endGameRes["winner"] = "white";
                        else endGameRes["winner"] = "black";
                        conn.send_text(endGameRes.dump());
                    }
                    else if (state == GameState::STALEMATE) {
                        std::cout << "STALEMATE";
                        endGameRes["type"] = "endgame";
                        endGameRes["game_state"] = "stalemate";
                        endGameRes["winner"] = "draw";
                        conn.send_text(endGameRes.dump());
                    }
                })
                .onclose([this](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
                    CROW_LOG_INFO << "Client disconnected : " << reason;
                });
        }

        GameState checkEndGame() {
            for (auto row: _board->_board) {
                for (auto cell: row) {
                    if (cell != nullptr && cell->_color == _currentTurn) {
                        std::vector<Move> possibleMoves = _moveGenerator->getPossibleMoves(_board->_board, {cell->_position.file, cell->_position.rank});
                        if (!possibleMoves.empty()) return GameState::CONTINUING;
                    }
                }
            }
            if (_moveGenerator->isKingInCheck(_currentTurn, _board->_board)) return GameState::CHECKMATE;
            else return GameState::STALEMATE;
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