export interface MoveRequest {
    gameId: number;
    from: string;
    to: string;
    promotion?: 'q' | 'r' | 'b' | 'n';
}