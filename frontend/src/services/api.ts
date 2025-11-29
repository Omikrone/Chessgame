import type { CreateGame } from "@/types";


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