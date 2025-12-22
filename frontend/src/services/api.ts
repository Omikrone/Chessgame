import type { CreateGame, GetGame } from "@/types";


export async function createGame(): Promise<CreateGame> {
    
    const apiUrl = import.meta.env.VITE_API_URL + "/games";

    const res = await fetch(apiUrl, {
        method: 'POST',
        headers: { "Content-Type": "application/json" },
    })
    
    if (!res.ok) {
        throw new Error("API error");
    }

    return res.json() as Promise<CreateGame>;
}

export async function getGame(gameId: number): Promise<GetGame> {
    const apiUrl = import.meta.env.VITE_API_URL + `/games/${gameId}`;
    const res = await fetch(apiUrl, {
        method: 'GET',
        headers: { "Content-Type": "application/json" },
    });

    if (!res.ok) {
        throw new Error("API error");
    }

    return res.json() as Promise<GetGame>;
}