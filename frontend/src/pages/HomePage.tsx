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
    <div className="h-screen flex flex-col items-center justify-center bg-gradient-to-br from-beige-light to-brown-light">
      <h1 className="text-4xl md:text-5xl font-bold text-brown-dark mb-10">
        Jeu d'échecs
      </h1>
      <button onClick={handleNewGame} className="px-8 py-4 bg-beige-light text-brown-dark font-semibold rounded-xl shadow-md hover:bg-brown-medium hover:text-beige-light transition duration-300">Créer une partie</button>
    </div>
  );
}