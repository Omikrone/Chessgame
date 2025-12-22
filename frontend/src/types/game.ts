export interface CreateGame {
    status : 'success' | 'error';
    gameId : number;
    playerColor : 'white' | 'black';
}

export interface GetGame {
    gameId : number;
    fen : string;
    playerColor : 'white' | 'black';
}