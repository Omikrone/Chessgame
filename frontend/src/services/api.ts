import type { CreateGameResponse } from "../types/game";

export async function createGame(): Promise<CreateGameResponse> {
    const apiUrl = 'http://127.0.0.1:18080/games';

    const res = await fetch(apiUrl, {
        method: 'POST',
        headers: { "Content-Type": "application/json" },
    })
    
    if (!res.ok) {
        throw new Error("API error");
    }

    return res.json() as Promise<CreateGameResponse>;
}