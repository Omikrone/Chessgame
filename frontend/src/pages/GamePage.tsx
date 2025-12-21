import { useEffect, useRef, useState, useMemo } from "react";
import { useLocation, useNavigate } from "react-router-dom";
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
  const location = useLocation();
  const playerColor = location.state?.playerColor || "white";
  
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

  const isPlayerTurn = useMemo(() => {
    if (fen === "start") {
      console.log("FEN is 'start', defaulting to white's turn");
      return playerColor === "white";
    }
    
    const fenParts = fen.split(' ');
    if (fenParts.length < 2) {
      console.log("Invalid FEN format:", fen);
      return false;
    }
    
    const turn = fenParts[1];
    console.log("Turn from FEN:", turn, "Player color:", playerColor);
    
    return (turn === 'w' && playerColor === 'white') || 
           (turn === 'b' && playerColor === 'black');
  }, [fen, playerColor]);

  console.log("GamePage render - isPlayerTurn:", isPlayerTurn, "fen:", fen, "playerColor:", playerColor);

  async function handleNewGame() {
    const newGame = await createGame();
    navigate(`/games/${newGame.gameId}`,
      { state: { playerColor: newGame.playerColor } }
    );
  }

  useEffect(() => {
    if (!gameId) return;

    const socket = createGameSocket((message: Position | ErrorResponse) => {
      console.log("Processing message:", message);
      
      if ('error' in message) {
        setError(message);
      } else {
        requestAnimationFrame(() => {
          console.log("Setting new FEN:", message.fen);
          setFen(message.fen);
          setUpdateId(id => id + 1);
          if (message.game_over) {
            setResult(message.result || null);
            setReason(message.reason || null);
            setWinner(message.winner || null);
          }
        });
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

    if (!isPlayerTurn) {
      console.log("Not player's turn, ignoring move. isPlayerTurn:", isPlayerTurn);
      return;
    }
    
    console.log("Move submitted :", {from, to, piece});

    if ((piece?.toLowerCase().at(0) === 'p') && (to[1] === '8' || to[1] === '1')) {
      setPromotionFrom(from);
      setPromotionTo(to);
      setPromotionColor(fen.split(' ')[1] === 'w' ? 'w' : 'b');
      return;
    }
    socketRef.current?.sendMove({gameId: Number(gameId), msgType: "move", from, to, promotion: undefined});
  }

  function handlePromotionSelected(piece: 'q' | 'r' | 'b' | 'n') {
    if (!gameId || !promotionFrom || !promotionTo || !piece) return;
    
    if (!isPlayerTurn) {
      console.log("Not player's turn, ignoring promotion");
      return;
    }
    
    socketRef.current?.sendMove({gameId: Number(gameId), msgType: "move", from: promotionFrom, to: promotionTo, promotion: piece});
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
      <div className="absolute top-4 left-1/2 transform -translate-x-1/2 bg-gray-800 text-white px-4 py-2 rounded-lg">
        {isPlayerTurn ? (
          <div className="flex items-center gap-2">
            <div className="w-3 h-3 bg-green-500 rounded-full animate-pulse"></div>
            <span>Your turn ({playerColor})</span>
          </div>
        ) : (
          <div className="flex items-center gap-2">
            <div className="w-3 h-3 bg-red-500 rounded-full"></div>
            <span>Opponent's turn</span>
          </div>
        )}
      </div>
      
      <ChessBoard
        fen={fen}
        updateId={updateId}
        onMove={(from, to, piece) => handleMoveSubmitted(from, to, piece)}
        orientation={playerColor}
        movable={isPlayerTurn}
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