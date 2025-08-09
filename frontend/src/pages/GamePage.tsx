import { useState, useEffect } from "react";
import ChessBoard from "../components/ChessBoard";
import { createGameSocket } from "../websocket/websocket";
import "@lichess-org/chessground/assets/chessground.brown.css";
import "./pieces.css";


type GamePageProps = {
  gameId: string;
};

type ServerMessage = {
  type: string;
  fen?: string;
};

export default function GamePage({ gameId }: GamePageProps) {
  const [fen, setFen] = useState("start");
  const [updateId, setUpdateId] = useState(0);
  const [socket, setSocket] = useState<ReturnType<typeof createGameSocket> | null>(null);

  useEffect(() => {
    const ws = createGameSocket((rawData: string) => {
      try {
        const data: ServerMessage = JSON.parse(rawData);
        console.log(data.fen);
        if (data.type === "fen" && data.fen) {
          setFen(data.fen);
          setUpdateId(id => id + 1);
        }
      } catch (e) {
        console.error("Invalid JSON from server:", rawData);
      }
    });
    setSocket(ws);

    return () => {
      ws?.close?.();
    };
  }, [gameId]);

  return (
    <ChessBoard
      fen={fen}
      updateId = {updateId}
      onMove={(from, to) => socket?.sendMove(from, to)}
    />
  );
}