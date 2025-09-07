import { useEffect, useRef, useState } from "react";
import ChessBoard from "../components/ChessBoard";
import { createGameSocket } from "../services/websocket";
import "@lichess-org/chessground/assets/chessground.brown.css";
import "./pieces.css";
import { useParams } from "react-router-dom";


export default function GamePage() {

  const { gameId } = useParams<{ gameId: string }>();
  
  const [fen, setFen] = useState("start");
  const [updateId, setUpdateId] = useState(0);
  const socketRef = useRef<ReturnType<typeof createGameSocket> | null>(null);

  useEffect(() => {
    if (!gameId) return;

    const socket = createGameSocket((message) => {
      if (message.type === "fen" && message.fen) {
        setFen(message.fen);
        setUpdateId(id => id + 1);
      }
    }, Number(gameId));
    socketRef.current = socket;

    return () => {
      socket.close();
      socketRef.current = null;
    }
  }, [gameId])

  function handleMoveSubmitted(from: string, to: string) {
    if (!gameId) return;
    socketRef.current?.sendMove({type: 'move', gameId: Number(gameId), from, to});
  }

  return (
    <>
      <ChessBoard
        fen={fen}
        updateId = {updateId}
        onMove={(from, to) => handleMoveSubmitted(from, to)}
      />
    </>
  );
}