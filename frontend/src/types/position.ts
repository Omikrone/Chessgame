export interface Position {
    fen: string;
    game_over: boolean;
    winner?: 'white' | 'black';
    result?: 'checkmate' | 'draw';
    reason?: 'stalemate' | 'insufficient_material' | 'draw_by_fifty_move_rule' | 'draw_by_75_move_rule' | 'draw_by_threefold_repetition' | 'win_on_time';
}