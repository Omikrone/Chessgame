#include "game/rules/move_validator.hpp"


MoveValidator::MoveValidator(GameBoard& gameBoard, GameHistory& history) 
: _board(gameBoard),
  _history(history) {}


std::vector<Move> MoveValidator::filter_legal_moves(std::vector<Move>& rawPossibleMoves, Color side) {
    
    std::vector<Move> withoutCastleMoves = filter_castle_moves(rawPossibleMoves, side);
    std::vector<Move> withoutCheckMoves = filter_check_moves(withoutCastleMoves, side);
    std::vector<Move> legalMoves = filter_enpassant_moves(withoutCheckMoves, side);
    return legalMoves;
}


std::vector<Move> MoveValidator::filter_enpassant_moves(std::vector<Move>& possibleMoves, Color side) {
    std::vector<Move> legalMoves;

    if (!_history.empty()) {
        const Move& lastMove = _history.last();
        Piece *pieceToTake = _board._board[lastMove.destPos.rank][lastMove.destPos.file].get();

        for (Move m: possibleMoves) {
            if (m.type == MoveType::EN_PASSANT) {
                Piece *piece = _board._board[m.initPos.rank][m.initPos.file].get();
                if (pieceToTake == nullptr || pieceToTake->_color == side || pieceToTake->_pieceType != PieceType::PAWN) continue;
                int8_t distance = lastMove.destPos.rank - lastMove.initPos.rank;
                if (distance != 2 && distance != -2) continue;
                if (lastMove.destPos.file == pieceToTake->_position.file && piece->_position.rank == pieceToTake->_position.rank) legalMoves.push_back(m);
            }
            else {
                legalMoves.push_back(m);
            }
        }
    }
    else {
        for (Move m: possibleMoves) {
            if (m.type != MoveType::EN_PASSANT) legalMoves.push_back(m);
        }
    }
    return legalMoves;
}


std::vector<Move> MoveValidator::filter_check_moves(std::vector<Move>& possibleMoves, Color side) {
    std::vector<Move> legalMoves;

    for (Move m: possibleMoves) {
        std::unique_ptr<GameBoard> simulatedBoard = _board.clone();
        simulatedBoard.get()->make_move(m);

        std::vector<Move> enemyMoves;
        Color enemyColor = (side == Color::WHITE) ? Color::BLACK : Color::WHITE;
        enemyMoves = MoveGenerator::get_all_possible_moves(*simulatedBoard, enemyColor);
        
        King& king = simulatedBoard.get()->get_king(side);
        if (!simulatedBoard.get()->is_square_attacked(enemyMoves, king._position)) {
            legalMoves.push_back(m);
        }
    }
    return legalMoves;
}


std::vector<Move> MoveValidator::filter_castle_moves(std::vector<Move>& possibleMoves, Color side) {
    std::vector<Move> legalMoves;
    std::vector<Move> enemyMoves;
    Color enemyColor = (side == Color::WHITE) ? Color::BLACK : Color::WHITE;
    enemyMoves = MoveGenerator::get_all_possible_moves(_board, enemyColor);

    for (Move m: possibleMoves) {
        Piece *piece = _board.get_piece_at(m.initPos);
        if (m.type == MoveType::CASTLE_KINGSIDE) {
            if (check_kingside_castle(piece, enemyMoves)) legalMoves.push_back(m);
        }
        else if (m.type == MoveType::CASTLE_QUEENSIDE) {
            if (check_queenside_castle(piece, enemyMoves)) legalMoves.push_back(m);
        }
        else {
            legalMoves.push_back(m);
        }
    }
    return legalMoves;
}


bool MoveValidator::check_kingside_castle(Piece *king, std::vector<Move>& ennemyPossibleMoves) {
    if (king->_hasMoved) return false;
    Piece *rook = _board._board[king->_position.rank][king->_position.file + 3].get();
    if (rook == nullptr || rook->_hasMoved) return false;
    if (_board.is_square_attacked(ennemyPossibleMoves, king->_position)) return false;
    for (int8_t f = BOARD_LENGTH - 2; f > king->_position.file; f--)
    {
        if (_board._board[king->_position.rank][f] != nullptr || _board.is_square_attacked(ennemyPossibleMoves, {f, king->_position.rank})) {
            return false;
        }
    }
    return true;
}


bool MoveValidator::check_queenside_castle(Piece *king, std::vector<Move>& ennemyPossibleMoves) {
    if (king->_hasMoved) return false;
    Piece *rook = _board._board[king->_position.rank][king->_position.file - 4].get();
    if (rook == nullptr || rook->_hasMoved) return false;
    if (_board.is_square_attacked(ennemyPossibleMoves, king->_position)) return false;
    for (int8_t f = 2; f < king->_position.file; f++)
    {
        if (_board._board[king->_position.rank][f] != nullptr || _board.is_square_attacked(ennemyPossibleMoves, {f, king->_position.rank})) return false;
    }
    return true;
}
