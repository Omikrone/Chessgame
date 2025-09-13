import type { CreateGameResponse } from "../types/game";

export async function createGame(): Promise<CreateGameResponse> {
    
    const apiUrl = 'https://chessgame-p0kd.onrender.com/games';

    const res = await fetch(apiUrl, {
        method: 'POST',
        headers: { "Content-Type": "application/json" },
    })
    
    if (!res.ok) {
        throw new Error("API error");
    }

    return res.json() as Promise<CreateGameResponse>;
}