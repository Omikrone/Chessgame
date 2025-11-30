export interface CreateGame {
    status : 'success' | 'error';
    gameId : number;
    playerColor : 'white' | 'black';
}
