import { useEffect, useRef, useState, useMemo } from "react";
import { useLocation, useNavigate } from "react-router-dom";
import ChessBoard from "../components/ChessBoard";
import { createGameSocket } from "../services/websocket";
import "@lichess-org/chessground/assets/chessground.brown.css";
import { useParams } from "react-router-dom";
import GameOverModal from "../components/GameOverModal";
import { createGame, getGame } from "../services/api";
import GithubButton from "../components/GithubButton";
import type { ErrorResponse, Position } from "@/types";
import { ErrorNotification } from "@/components/ErrorNotification";
import PromotionModal from "@/components/PromotionModal";

export default function GamePage() {
  const { gameId } = useParams<{ gameId: string }>();
  const location = useLocation();
  console.log("GamePage location.state:", location.state);

  const isNewGame = location.state?.isNewGame || false;
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

  const [isGameLoaded, setIsGameLoaded] = useState(false);

  const isPlayerTurn = useMemo(() => {
    if (fen === "start") {
      return playerColor === "white";
    }
    
    const fenParts = fen.split(' ');
    if (fenParts.length < 2) {
      return false;
    }
    
    const turn = fenParts[1];
    
    return (turn === 'w' && playerColor === 'white') || 
           (turn === 'b' && playerColor === 'black');
  }, [fen, playerColor]);

  async function handleNewGame() {
    const newGame = await createGame();
    navigate(`/games/${newGame.gameId}`, {
      state: { 
        playerColor: newGame.playerColor,
        isNewGame: true
      }
    });
  }

  useEffect(() => {
    if (!gameId) return;

    const loadGameState = async () => {
      try {
        console.log("Loading game, isNewGame:", isNewGame);

        if (isNewGame) {
          console.log("New game detected, using start FEN");
          setFen("start");
          setIsGameLoaded(true);
          return;
        }

        console.log("Loading existing game state from API for gameId:", gameId);
        const gameData = await getGame(Number(gameId));
        
        if (gameData.fen && gameData.fen !== fen) {
          console.log("Setting initial FEN from API:", gameData.fen);
          setFen(gameData.fen);
        }
        
        setIsGameLoaded(true);
      } catch (err) {
        console.error("Failed to load game state:", err);
        setError({
          code: 404,
          error: "Game not found or failed to load"
        });
        setIsGameLoaded(true);
      }
    };

    loadGameState();
  }, [gameId, isNewGame]);

  useEffect(() => {
    if (!gameId || !isGameLoaded) return;

    console.log("Creating WebSocket, isNewGame for socket:", isNewGame);
    
    const socket = createGameSocket((message: Position | ErrorResponse) => {
      console.log("Processing message:", message);
      
      if ('error' in message) {
        setError(message);
      } else {
        requestAnimationFrame(() => {
          setFen(message.fen);
          setUpdateId(id => id + 1);
          if (message.game_over) {
            setResult(message.result || null);
            setReason(message.reason || null);
            setWinner(message.winner || null);
          }
        });
      }
    }, Number(gameId), isNewGame);
    
    socketRef.current = socket;

    return () => {
      socket.close();
      socketRef.current = null;
    }
  }, [gameId, isGameLoaded, isNewGame]);

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

  if (!isGameLoaded) {
    return (
      <div className="h-screen flex items-center justify-center p-max bg-beige-light">
        <div className="text-xl text-brown-dark">Loading game...</div>
      </div>
    );
  }

  return (
    <div className="h-screen flex items-center justify-center p-max bg-beige-light">
      <div className="absolute top-4 left-1/2 transform -translate-x-1/2 bg-gray-800 text-white px-4 py-2 rounded-lg">
        {isPlayerTurn ? (
          <div className="flex items-center gap-2">
            <div className="w-3 h-3 bg-green-500 rounded-full animate-pulse"></div>
            <span>Votre tour ({playerColor})</span>
          </div>
        ) : (
          <div className="flex items-center gap-2">
            <div className="w-3 h-3 bg-red-500 rounded-full"></div>
            <span>Au tour de l'adversaire</span>
          </div>
        )}
      </div>
      
      <ChessBoard
        fen={fen}
        updateId={updateId}
        onMove={(from, to, piece) => handleMoveSubmitted(from, to, piece)}
        orientation={playerColor}
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