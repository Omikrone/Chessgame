import "@lichess-org/chessground/assets/chessground.brown.css";
import "./pieces.css";
import { createGame } from "../services/api";
import { useNavigate } from "react-router-dom";



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