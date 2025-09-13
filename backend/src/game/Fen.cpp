#include "game/fen.hpp"


std::string FEN::to_string(Game& game) {
    std::string fen;

    GameBoard& board = game.get_game_board();
    for (int8_t i=BOARD_LENGTH - 1; i >= 0; i--) {
        int8_t wo_piece = 0;
        for (int8_t j=0; j < BOARD_LENGTH; j++) {
            if (board._board[i][j].get() != nullptr) {
                if (wo_piece != 0) {
                    fen.append(std::to_string(wo_piece));
                    wo_piece = 0;
                }
                fen.push_back(board._board[i][j]->to_fen());
            }
            else {
                wo_piece++;
            }
        }
        if (wo_piece != 0) fen.append(std::to_string(wo_piece));
        fen.push_back('/');
    }
    fen.pop_back(); // Remove the last '/'

    if (game.get_current_turn() == Color::WHITE) fen.append(" w ");
    else fen.append(" b ");
    
    fen.append("KQkq - ");
    fen.append(std::to_string(game.get_nb_moves(Color::BLACK)));
    fen.push_back(' ');
    fen.append(std::to_string(game.get_nb_moves(Color::WHITE)));

    return fen;
}