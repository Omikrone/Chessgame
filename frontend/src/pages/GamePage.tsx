import { useEffect, useRef, useState } from "react";
import { useNavigate } from "react-router-dom";
import ChessBoard from "../components/ChessBoard";
import { createGameSocket } from "../services/websocket";
import "@lichess-org/chessground/assets/chessground.brown.css";
import { useParams } from "react-router-dom";
import GameOverModal from "../components/GameOverModal";
import { createGame } from "../services/api";
import GithubButton from "../components/GithubButton";
import type { ErrorResponse, Position } from "@/types";
import { ErrorNotification } from "@/components/ErrorNotification";
import PromotionModal from "@/components/PromotionModal";


export default function GamePage() {

  const { gameId } = useParams<{ gameId: string }>();
  
  const [fen, setFen] = useState("start");
  const [updateId, setUpdateId] = useState(0);
  const socketRef = useRef<ReturnType<typeof createGameSocket> | null>(null);
  const [result, setResult] = useState<"checkmate" | "draw" | "timeout" | null>(null);
  const [reason, setReason] = useState<'stalemate' | 'insufficient_material' | 'draw_by_fifty_move_rule' | 'draw_by_75_move_rule' | 'draw_by_threefold_repetition' | 'win_on_time' | null>(null);
  const [winner, setWinner] = useState<"white" | "black" | null>(null);
  const [error, setError] = useState<ErrorResponse | null>(null);
  const [promotionColor, setPromotionColor] = useState<'w' | 'b' | null>(null);
  const [promotionFrom, setPromotionFrom] = useState<string | null>(null);
  const [promotionTo, setPromotionTo] = useState<string | null>(null);
  const navigate = useNavigate();

  async function handleNewGame() {
    const newGame = await createGame();
    navigate(`/games/${newGame.gameId}`);
  }

  useEffect(() => {
    if (!gameId) return;

    const socket = createGameSocket((message: Position | ErrorResponse) => {
      if ('error' in message) {
        setError(message);
      } else {
        setFen(message.fen);
        setUpdateId(id => id + 1);
        if (message.game_over) {
          setResult(message.result || null);
          setReason(message.reason || null);
          setWinner(message.winner || null);
        }
      }
    }, Number(gameId));
    socketRef.current = socket;

    return () => {
      socket.close();
      socketRef.current = null;
    }
  }, [gameId])

  function handleMoveSubmitted(from: string, to: string, piece?: string) {
    if (!gameId) return;
    console.log("Move submitted :", {from, to, piece});

    if ((piece?.toLowerCase().at(0) === 'p') && (to[1] === '8' || to[1] === '1')) {
      setPromotionFrom(from);
      setPromotionTo(to);
      setPromotionColor(fen.split(' ')[1] === 'w' ? 'w' : 'b');
      return;
    }
    socketRef.current?.sendMove({gameId: Number(gameId), from, to, promotion: undefined});
  }

  function handlePromotionSelected(piece: 'q' | 'r' | 'b' | 'n') {
    if (!gameId || !promotionFrom || !promotionTo || !piece) return;
    socketRef.current?.sendMove({gameId: Number(gameId), from: promotionFrom, to: promotionTo, promotion: piece});
    setPromotionColor(null);
    setPromotionFrom(null);
    setPromotionTo(null);
  }

  function handleOnRestart() {
    setResult(null);
    setReason(null);
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
        onMove={(from, to, piece) => handleMoveSubmitted(from, to, piece)}
      />
      <GithubButton/>
      {result ?(
        <GameOverModal result={result} reason={reason} winner={winner} onRestart={handleOnRestart}/>
      ) : null}
      {promotionColor ? (
        <PromotionModal
          color={promotionColor === 'w' ? 'white' : 'black'}
          onSelect={handlePromotionSelected}
        />
      ) : null}
      {error ? (
        <ErrorNotification
          error={error}
          onClose={() => setError(null)}
        />
      ) : null}
    </div>
  );
}