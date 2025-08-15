#include "Fen.hpp"


class Fen
{

public:

    std::string toString(const GameBoard& board) {
        std::string fen;

        for (int8_t i=BOARD_LENGTH - 1; i >= 0; i--) {
            int8_t wo_piece = 0;
            for (int8_t j=0; j < BOARD_LENGTH; j++) {
                if (board._board[i][j] != nullptr) {
                    if (wo_piece != 0) {
                        fen.append(std::to_string(wo_piece));
                        wo_piece = 0;
                    }
                    fen.push_back(board._board[i][j]->toFEN());
                }
                else {
                    wo_piece++;
                }
            }
            if (wo_piece != 0) fen.append(std::to_string(wo_piece));
            fen.push_back('/');
        }
        fen.pop_back(); // Remove the last '/'
        return fen;
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
};