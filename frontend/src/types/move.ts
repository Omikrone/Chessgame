export interface MoveRequest {
    gameId: number;
    msgType: "move";
    from: string;
    to: string;
    promotion?: 'q' | 'r' | 'b' | 'n';
}