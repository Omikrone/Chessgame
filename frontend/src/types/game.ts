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

export type ServerResponse = MoveResponse | EndGameResponse;

export interface MoveResponse {
    type: 'fen';
    fen: string;
}

export interface EndGameResponse {
    type: 'endgame';
    fen: string;
    result: 'checkmate' | 'draw';
    winner?: 'white' | 'black'
}