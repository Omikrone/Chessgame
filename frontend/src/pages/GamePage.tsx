import { useEffect, useRef, useState } from "react";
import { useNavigate } from "react-router-dom";
import ChessBoard from "../components/ChessBoard";
import { createGameSocket } from "../services/websocket";
import "@lichess-org/chessground/assets/chessground.brown.css";
import { useParams } from "react-router-dom";
import GameOverModal from "../components/GameOverModal";
import { createGame } from "../services/api";
import GithubButton from "../components/GithubButton";


export default function GamePage() {

  const { gameId } = useParams<{ gameId: string }>();
  
  const [fen, setFen] = useState("start");
  const [updateId, setUpdateId] = useState(0);
  const socketRef = useRef<ReturnType<typeof createGameSocket> | null>(null);
  const [result, setResult] = useState<"checkmate" | "draw" | "stalemate" | "timeout" | null>(null);
  const [winner, setWinner] = useState<"white" | "black" | null>(null);
  const navigate = useNavigate();

  async function handleNewGame() {
    const newGame = await createGame();
    navigate(`/games/${newGame.gameId}`);
  }


  useEffect(() => {
    if (!gameId) return;

    const socket = createGameSocket((message) => {
      if (message.fen) {
        setFen(message.fen);
        setUpdateId(id => id + 1);
      }
      if (message.game_over) {
        setResult(message.reason || null);
        setWinner(message.winner || null);
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
    socketRef.current?.sendMove({gameId: Number(gameId), from, to});
  }

  function handleOnRestart() {
    setResult(null);
    setWinner(null);
    setUpdateId(0);
    setFen("start");
    handleNewGame();
  }

  return (
    <div className="h-screen flex items-center justify-center p-max bg-beige-light">
      <ChessBoard
        fen={fen}
        updateId = {updateId}
        onMove={(from, to) => handleMoveSubmitted(from, to)}
      />
      <GithubButton/>
      {result ?(
        <GameOverModal result={result} winner={winner} onRestart={handleOnRestart}/>
      ) : null}
    </div>
  );
}