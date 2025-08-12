
#include "board.hpp"
#include "pieces/utils/move.hpp"

class MoveGenerator {
public:

    GameBoard *_board;

    MoveGenerator(GameBoard *board) {
        _board = board;
    }


    std::vector<Move> convertToMoves(std::vector<std::vector<Piece*>> board, std::vector<std::vector<Position>> rawMoves, Piece *piece) {
        
        std::vector<Move> legalMoves;

        if (piece->_pieceType == Type::PAWN) {

            // Forward
            if (rawMoves.size() > 0) {
                for (Position p: rawMoves[0]) {
                    Piece *presentPiece = board[p.rank][p.file];
                    if (presentPiece != nullptr) {
                        break;
                    }
                    else {
                        legalMoves.push_back({piece->_position, p, MoveType::TRAVEL});
                    }
                }
            }

            // Side take
            if (rawMoves.size() > 1) {
                for (int i = 1; i < rawMoves.size(); i++)
                {
                    Position takePosition = rawMoves[i][0];
                    Piece *presentPiece = board[takePosition.file][takePosition.rank];
                    if (presentPiece != nullptr && presentPiece->_color != piece->_color)
                    {
                        legalMoves.push_back({piece->_position, takePosition, MoveType::TAKE});
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
                        legalMoves.push_back({piece->_position, p, MoveType::TAKE});
                        break;
                    }
                    else {
                        legalMoves.push_back({piece->_position, p, MoveType::TRAVEL});
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
                        legalMoves.push_back({piece->_position, p, MoveType::TAKE});
                        break;
                    }
                    else {
                        legalMoves.push_back({piece->_position, p, MoveType::TRAVEL});
                    }
                }
            }
        }
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
            m.initPos.print();
            m.destPos.print();
            _board->makeMove(simulatedBoard, m);
            std::cout << "Move finished" << std::endl;
            
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
                else std::cout << "CASTLE NOT ALLOWED";
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
            return false; // ou true si tu veux traiter ça comme une position illégale
        }
        
        king->_position.print();

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


    void Castle(std::vector<std::vector<Piece*>> &board, Piece *piece, bool queenside) {
        if (piece->_hasMoved || isKingInCheck(piece->_color, board)) return;
        if (piece->_color == Color::WHITE && queenside) {
            
            if (board[0][0] != nullptr && board[0][0]->toFEN() == 'R' && !board[0][0]->_hasMoved) {
                std::cout << "coucou" << std::endl;
                for (int8_t i = piece->_position.file - 1; i > 0; i--) {
                    if (board[0][i] != nullptr) return;
                }
                piece->_position.file -= 2;
                _board->makeMove(board, {{0, 0}, {0, 3}, MoveType::CASTLE_KINGSIDE});
            }
        }
    }
};