#include "game/board/pieces/utils/Square.hpp"
#include "game/board/pieces/utils/Move.hpp"
#include "api/models/requests.hpp"


class Parser {
public:
    static Square parsePosition(PossibleMovesReq req);
    static Move parseMove(MakeMoveReq req);
};
