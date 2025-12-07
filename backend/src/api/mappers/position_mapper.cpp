#include "api/mappers/position_mapper.hpp"

PositionResponse PositionMapper::to_position_response(const GameState game_state, const std::string& fen,
                                                      Color current_turn) {
    PositionResponse response;
    response.fen = fen;
    response.game_over = (game_state != GameState::CONTINUING);

    switch (game_state) {
        case GameState::CHECKMATE:
            response.winner = (current_turn == Color::WHITE) ? "black" : "white";
            response.result = "checkmate";
            break;
        case GameState::STALEMATE:
            response.result = "draw";
            response.reason = "stalemate";
            break;
        case GameState::DRAW_BY_INSUFFICIENT_MATERIAL:
            response.result = "draw";
            response.reason = "insufficient_material";
            break;
        case GameState::DRAW_BY_FIFTY_MOVE_RULE:
            response.result = "draw";
            response.reason = "draw_by_fifty_move_rule";
            break;
        case GameState::DRAW_BY_75_MOVE_RULE:
            response.result = "draw";
            response.reason = "draw_by_75_move_rule";
            break;
        case GameState::DRAW_BY_THREEFOLD_REPETITION:
            response.result = "draw";
            response.reason = "draw_by_threefold_repetition";
            break;
        default:
            break;
    }

    return response;
}