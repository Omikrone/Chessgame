import type { MoveRequest, MoveResponse } from "../types/game";


type GameMessageHandler = (message : MoveResponse) => void;


export function createGameSocket(onMessage : GameMessageHandler, gameId: number) {

  const ws = new WebSocket(`ws://localhost:18080/ws/${gameId}`);

  ws.onopen = () => {
    console.log("WebSocket connected");
  };

  ws.onmessage = (event) => {
    console.log("Message received :", event.data);
    try {
      const parsed = JSON.parse(event.data) as MoveResponse;
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