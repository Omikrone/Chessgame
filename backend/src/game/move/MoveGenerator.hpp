#include "../board/Board.hpp"
#include "pieces/utils/move.hpp"


class MoveGenerator
{
    private:
        GameBoard& _board;
    public:
        MoveGenerator(GameBoard& board);
        ~MoveGenerator();

        std::vector<Move> getRawPossibleMoves(Piece *piece);
};
