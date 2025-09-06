import type { MoveRequest, MoveResponse } from "../types/game";


type GameMessageHandler = (message : MoveResponse) => void;


export function createGameSocket(onMessage : GameMessageHandler, gameId: number) {

  const ws = new WebSocket(`ws://localhost:18080/ws/${gameId}`);

  ws.onopen = () => {
    console.log("WebSocket connected");
  };

  ws.onmessage = (event) => {
    console.log("Message received :", event.data);
    onMessage(event.data)
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