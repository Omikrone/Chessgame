import type { MoveRequest, Position } from "@/types";


type GameMessageHandler = (message : Position) => void;


export function createGameSocket(onMessage : GameMessageHandler, gameId: number) {

  const ws = new WebSocket(import.meta.env.VITE_WS_URL + `/ws/${gameId}`);

  ws.onopen = () => {
    console.log("WebSocket connected");
  };

  ws.onmessage = (event) => {
    console.log("Message received :", event.data);
    try {
      const parsed = JSON.parse(event.data) as Position;
      onMessage(parsed);
    } catch (error) {
      console.error("Invalid message received:", event.data, error);
    }
  };

  ws.onclose = () => {
    console.log("WebSocket closed");
  };

  return {
    sendMove: (move: MoveRequest) => {
      ws.send(JSON.stringify(move));
    },
    close: () => ws.close(),
  };
}