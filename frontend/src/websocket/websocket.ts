type GameMessageHandler = (message : string) => void;

export function createGameSocket(onMessage : GameMessageHandler) {

  const ws = new WebSocket("ws://localhost:18080/ws");

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
    sendMove: (from : string, to : string) => {
      ws.send(JSON.stringify({type: "move", from, to}));
    },
    close: () => ws.close(),
  };
}