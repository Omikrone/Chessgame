import type { ErrorResponse, MoveRequest, Position, Request } from "@/types";

type GameMessageHandler = (message: Position | ErrorResponse) => void;

export function createGameSocket(onMessage: GameMessageHandler, gameId: number) {
  const ws = new WebSocket(import.meta.env.VITE_WS_URL + `/ws/${gameId}`);

  let connectionEstablished = false;
  const messageQueue: any[] = [];

  ws.onopen = () => {
    console.log("WebSocket connected");
    connectionEstablished = true;
    const initRequest: Request = { msgType: "init", gameId };
    ws.send(JSON.stringify(initRequest));
    
    messageQueue.forEach(msg => ws.send(JSON.stringify(msg)));
    messageQueue.length = 0;
  };

  ws.onmessage = (event) => {
    console.log("Message received :", event.data);
    try {
      const parsed = JSON.parse(event.data);
      onMessage(parsed);
    } catch (error) {
      console.error("Invalid message received:", event.data, error);
    }
  };

  ws.onclose = () => {
    console.log("WebSocket closed");
    connectionEstablished = false;
  };

  ws.onerror = (error) => {
    console.error("WebSocket error:", error);
  };

  return {
    sendMove: (move: MoveRequest) => {
      if (connectionEstablished && ws.readyState === WebSocket.OPEN) {
        console.log("Sending move:", move);
        ws.send(JSON.stringify(move));
      } else {
        console.log("WebSocket not ready, queuing message");
        messageQueue.push(move);
      }
    },
    close: () => ws.close(),
  };
}