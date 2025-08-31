#include "GameSession.hpp"


GameSession::GameSession() {
    _game = new Game();
}


GameSession::onMoveReceived(std::string rawMove) {
                
    std::string from = body["from"].s();
    std::string to = body["to"].s();
    Square initPos = convertInputToPos(from);
    Square destPos = convertInputToPos(to);
    CROW_LOG_INFO << "New message : " << data;

    std::vector<Move> possibleMoves = _moveGenerator->getPossibleMoves(_board->_board, initPos);

    _board->printBoard(_board->_board);

    crow::json::wvalue response;
    response["type"] = "fen";
    response["fen"] = toFEN();

    conn.send_text(response.dump());
    
    GameState state = checkEndGame();
    crow::json::wvalue endGameRes;
}


Square convertInputToPos(std::string pos) {
    Square position;
    int8_t file = pos.at(0) - 'a'; // Convert letter (i.e. 'a') to array indice (i.e. 0)
    int8_t rank = pos.at(1) - '1';
    position = {file, rank};
    return position;
}