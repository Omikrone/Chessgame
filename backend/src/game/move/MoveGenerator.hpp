#include "../board/Board.hpp"
#include "../board/pieces/utils/Move.hpp"


class MoveGenerator
{
    private:
        GameBoard& _board;
    public:
        MoveGenerator(GameBoard& board);
        ~MoveGenerator();

        std::vector<Move> getAllPossibleMoves(Color side);
        std::vector<Move> getPossibleMoves(Piece *piece);
};
