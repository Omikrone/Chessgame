#include "Board.hpp"


class FEN
{
public:
    static void load(GameBoard& board, const std::string& fen);
    static std::string toString(const GameBoard& board);
};