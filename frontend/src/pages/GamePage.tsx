import { useState, useEffect } from "react";
import ChessBoard from "../components/ChessBoard";
import { createGameSocket } from "../websocket/websocket";
import "@lichess-org/chessground/assets/chessground.brown.css";
import "./pieces.css";
import GameOverModal from "../components/GameOverModal";


type GamePageProps = {
  gameId: string;
};

type ServerMessage = {
  type: "fen" | "endgame";
  fen?: string;
  game_state?: "checkmate" | "stalemate";
  winner?: "black" | "white";
};

export default function GamePage({ gameId }: GamePageProps) {
  const [fen, setFen] = useState("start");
  const [updateId, setUpdateId] = useState(0);
  const [socket, setSocket] = useState<ReturnType<typeof createGameSocket> | null>(null);
  const [winner, setWinner] = useState<"black" | "white" | null>(null);

  
  const restartGame = () => {
    setWinner(null);
  };

  useEffect(() => {
    const ws = createGameSocket((rawData: string) => {
      try {
        fetch()
        const data: ServerMessage = JSON.parse(rawData);
        if (data.type === "fen" && data.fen) {
          setFen(data.fen);
          setUpdateId(id => id + 1);
        }
        else if (data.type === "endgame") {
          setWinner(data.winner ?? null);
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
    <>
      <ChessBoard
        fen={fen}
        updateId = {updateId}
        onMove={(from, to) => socket?.sendMove(from, to)}
      />
      
      {winner && (
        <GameOverModal winner={winner} onRestart={restartGame} />
      )}
    </>
  );
}