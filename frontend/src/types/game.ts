export interface CreateGameResponse {
    status : 'success' | 'error';
    gameId : number;
}

export interface MoveRequest {
    type: 'move';
    gameId: number;
    from: string;
    to: string;
}

export interface MoveResponse {
    type: 'fen';
    fen: string;
}