import "./GameOverModal.css"

type GameOverModalProps = {
    winner?: "white" | "black" | "draw" | null;
    onRestart: () => void;
}


export default function GameOverModal({ winner, onRestart }: GameOverModalProps) {
  if (!winner) return null;

  return (
    <div className="game-over-overlay">
      {winner === "draw" ? (
        <p>Match nul !</p>
      ) : winner === "black" ? (
        <p>Les Noirs ont gagné !</p>
      ) : (
        <p>Les Blancs ont gagné !</p>
      )}
      <button onClick={onRestart}>Rejouer</button>
    </div>
  );
}