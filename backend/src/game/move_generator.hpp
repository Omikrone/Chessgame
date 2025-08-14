
#include "board.hpp"
#include "pieces/utils/move.hpp"

class MoveGenerator {
public:

    GameBoard *_board;
    std::vector<Move> _history;
    

    MoveGenerator(GameBoard *board) {
        _board = board;
    }


    std::vector<Move> convertToMoves(std::vector<std::vector<Piece*>> board, std::vector<std::vector<Position>> rawMoves, Piece *piece) {
        
        std::vector<Move> legalMoves;

        if (piece->_pieceType == Type::PAWN) {

            for (std::vector<Position> dm: rawMoves) {

                // Forward
                if (dm[0].file == piece->_position.file) {
                    for (Position p: dm) {
                        Piece *presentPiece = board[p.rank][p.file];
                        if (presentPiece != nullptr) {
                            break;
                        }
                        else if (p.rank == BOARD_LENGTH - 1 || p.rank == 0) {
                            legalMoves.push_back({piece->_position, p, MoveType::PROMOTION, false});
                        }
                        else {
                            legalMoves.push_back({piece->_position, p, MoveType::NORMAL, false});
                        }
                    }
                }

                // Side take
                else {
                    Position takePosition = dm[0];
                    Piece *presentPiece = board[takePosition.rank][takePosition.file];
                    if (presentPiece != nullptr && presentPiece->_color != piece->_color)
                    {
                        if (takePosition.rank == BOARD_LENGTH - 1 || takePosition.rank == 0) {
                            legalMoves.push_back({piece->_position, takePosition, MoveType::PROMOTION, true});
                        }
                        else {
                            legalMoves.push_back({piece->_position, takePosition, MoveType::NORMAL, true});
                        }
                    }
                    else if (takePosition.rank == BOARD_LENGTH - 1 || takePosition.rank == 0) {
                        
                    }
                    else if (_history.size() > 0 && checkEnPassant(board, piece, &takePosition, _history.back())) {
                        legalMoves.push_back({piece->_position, takePosition, MoveType::EN_PASSANT, true});
                    }
                }
            }
        }

        else if (piece->_pieceType == Type::KING) {
            for (std::vector<Position> dm: rawMoves)
            {
                for (Position p: dm) {
                    int8_t distance  = p.file - piece->_position.file;
                    Piece *presentPiece = board[p.rank][p.file];
                    if (distance == 2) legalMoves.push_back({piece->_position, p, MoveType::CASTLE_KINGSIDE});
                    else if (distance == -2) legalMoves.push_back({piece->_position, p, MoveType::CASTLE_QUEENSIDE});
                    else if (presentPiece != nullptr && presentPiece->_color == piece->_color) {
                        break;
                    }
                    else if (presentPiece != nullptr && presentPiece->_color != piece->_color) {
                        legalMoves.push_back({piece->_position, p, MoveType::NORMAL, true});
                        break;
                    }
                    else {
                        legalMoves.push_back({piece->_position, p, MoveType::NORMAL, false});
                    }
                }
            }
        }
        else {

            for (std::vector<Position> dm: rawMoves)
            {
                for (Position p: dm) {
                    Piece *presentPiece = board[p.rank][p.file];
                    if (presentPiece != nullptr && presentPiece->_color == piece->_color) {
                        break;
                    }
                    else if (presentPiece != nullptr && presentPiece->_color != piece->_color) {
                        legalMoves.push_back({piece->_position, p, MoveType::NORMAL, true});
                        break;
                    }
                    else {
                        legalMoves.push_back({piece->_position, p, MoveType::NORMAL, false});
                    }
                }
            }
        }
        return legalMoves;
    }

    bool checkEnPassant(std::vector<std::vector<Piece*>> board, Piece *piece, Position *takePosition, Move lastMove) {
        Piece *pieceToTake = board[lastMove.destPos.rank][lastMove.destPos.file];
        if (pieceToTake == nullptr || pieceToTake->_color == piece->_color || pieceToTake->_pieceType != Type::PAWN) return false;
        int8_t distance = lastMove.destPos.rank - lastMove.initPos.rank;
        if (distance != 2 && distance != -2) return false;
        if (takePosition->file == pieceToTake->_position.file && piece->_position.rank == pieceToTake->_position.rank) return true;
    }


    std::vector<Move> getPossibleMoves(std::vector<std::vector<Piece*>> board, Position initPos) {
        Piece *piece = _board->_board[initPos.rank][initPos.file];
        
        std::vector<Move> possibleMoves = getLegalMoves(_board->_board, initPos);
        std::vector<Move> withoutCastleMoves = filterCastleMoves(&piece->_position, possibleMoves);
        std::vector<Move> legalMoves = filterCheckMoves(&piece->_position, withoutCastleMoves);  
        return legalMoves;
    }


    std::vector<Move> getLegalMoves(std::vector<std::vector<Piece*>> board, Position piecePosition) {
        Piece *piece = board[piecePosition.rank][piecePosition.file];
        std::vector<std::vector<Position>> rawMoves = piece->getRawMoves();

        std::vector<Move> possibleMoves = convertToMoves(board, rawMoves, piece);

        return possibleMoves;
    }


    std::vector<Move> filterCheckMoves(Position *piecePosition, std::vector<Move> possibleMoves) {
        std::vector<Move> legalMoves;
        std::vector<std::vector<Piece *>> simulatedBoard;

        Piece *piece = _board->_board[piecePosition->rank][piecePosition->file];

        for (Move m: possibleMoves) {
            simulatedBoard = deepCopyBoard(_board->_board);
            _board->makeMove(simulatedBoard, m);
            
            if (!isKingInCheck(piece->_color, simulatedBoard)) {
                legalMoves.push_back(m);
            }
            
            for (auto& row : simulatedBoard) {
                for (auto& cell : row) {
                    delete cell;
                }
            }
        }
        return legalMoves;
    }

    std::vector<Move> filterCastleMoves(Position *piecePosition, std::vector<Move> possibleMoves) {
        std::vector<Move> legalMoves;

        Piece *piece = _board->_board[piecePosition->rank][piecePosition->file];
        if (piece->_pieceType != Type::KING) return possibleMoves;

        for (Move m: possibleMoves) {
            if (m.type == MoveType::CASTLE_KINGSIDE) {
                if (checkKingSideCastle(piece)) legalMoves.push_back(m);
            }
            else if (m.type == MoveType::CASTLE_QUEENSIDE) {
                if (checkQueenSideCastle(piece)) legalMoves.push_back(m);
            }
            else {
                legalMoves.push_back(m);
            }
        }
        return legalMoves;
    }


    bool checkKingSideCastle(Piece *king) {
        if (king->_hasMoved) return false;
        Piece *rook = _board->_board[king->_position.rank][king->_position.file + 3];
        if (rook == nullptr || rook->_hasMoved) return false;
        if (isSquareAttacked(king->_position, _board->_board, king->_color)) return false;
        for (int8_t f = BOARD_LENGTH - 2; f > king->_position.file; f--)
        {
            if (_board->_board[king->_position.rank][f] != nullptr || isSquareAttacked({f, king->_position.rank}, _board->_board, king->_color)) {
                return false;
            }
        }
        return true;
    }

    bool checkQueenSideCastle(Piece *king) {
        if (king->_hasMoved) return false;
        Piece *rook = _board->_board[king->_position.rank][king->_position.file - 4];
        if (rook == nullptr || rook->_hasMoved) return false;
        if (isSquareAttacked(king->_position, _board->_board, king->_color)) return false;
        for (int8_t f = 1; f < king->_position.file; f++)
        {
            if (_board->_board[king->_position.rank][f] != nullptr || isSquareAttacked({f, king->_position.rank}, _board->_board, king->_color)) return false;
        }
        return true;
    }


    std::vector<std::vector<Piece*>> deepCopyBoard(const std::vector<std::vector<Piece*>>& board) {
        std::vector<std::vector<Piece*>> copy(board.size(), std::vector<Piece*>(board[0].size(), nullptr));

        for (int8_t r = 0; r < board.size(); r++) {
            for (int8_t f = 0; f < board[r].size(); f++) {
                if (board[r][f] != nullptr) {
                    copy[r][f] = board[r][f]->clone();
                }
            }
        }
        return copy;
    }


    bool isKingInCheck(Color kingColor, std::vector<std::vector<Piece*>> board) {
        Piece *king = _board->findKing(board, kingColor);
        if (!king) {
            std::cerr << "Erreur : Roi introuvable !" << std::endl;
            return false;
        }

        return isSquareAttacked(king->_position, board, king->_color);
    }


    bool isSquareAttacked(Position position, std::vector<std::vector<Piece*>> board, Color color) {
        for (int8_t i = 0; i < BOARD_LENGTH; i++)
        {
            for (int8_t j = 0; j < BOARD_LENGTH; j++)
            {
                if (board[i][j] == nullptr || board[i][j]->_color == color) continue;
                else {
                    std::vector<Move> possibleMoves = getLegalMoves(board, {j, i});
                    for (Move m: possibleMoves)
                    {
                        if (m.destPos == position) {
                            return true;
                        }
                    }
                    
                } 
            }
        }
        return false;
    }
};