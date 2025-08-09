type GameMessageHandler = (message : string) => void;

export function createGameSocket(onMessage : GameMessageHandler) {

  const ws = new WebSocket("ws://localhost:18080/ws");

  ws.onopen = () => {
    console.log("WebSocket connected");
    ws.send("Hello server !");
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
      console.log("from "+ from + " to " + to);
      ws.send(JSON.stringify({type: "move", from, to}));
      return true;
    },
    close: () => ws.close(),
  };
}