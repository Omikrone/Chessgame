export interface Position {
    fen: string;
    game_over: boolean;
    winner?: 'white' | 'black';
    reason?: 'checkmate' | 'draw' | 'stalemate' | 'timeout';
}