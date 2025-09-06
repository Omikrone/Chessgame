import "@lichess-org/chessground/assets/chessground.brown.css";
import "./pieces.css";
import { createGame } from "../services/api";
import { Link, useNavigate } from "react-router-dom";
import { useState } from "react";



export default function HomePage() {

  const navigate = useNavigate();

  async function handleNewGame() {
    const newGame = await createGame();
    navigate(`/games/${newGame.gameId}`);
  }

  return (
    <>
      <button onClick={handleNewGame}>Créer une partie</button>
    </>
  );
}