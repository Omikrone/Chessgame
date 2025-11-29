type GameOverModalProps = {
    result: "checkmate" | "draw" | "timeout";
    reason:  'stalemate' | 'insufficient_material' | 'draw_by_fifty_move_rule' | 'draw_by_75_move_rule' | 'draw_by_threefold_repetition' | 'win_on_time' | null;
    winner: "white" | "black" | null;
    onRestart: () => void;
}


export default function GameOverModal({ result, reason, winner, onRestart }: GameOverModalProps) {
  if (!winner && result !== "draw" && result !== "timeout") return null;

  let description = "";
  switch (reason) {
    case 'insufficient_material':
      description = "Matériel insuffisant pour mater.";
      break;
    case 'draw_by_fifty_move_rule':
      description = "Partie nulle par la règle des 50 coups.";
      break;
    case 'draw_by_75_move_rule':
      description = "Partie nulle par la règle des 75 coups.";
      break;
    case 'draw_by_threefold_repetition':
      description = "Partie nulle par la répétition triple.";
      break;
    case 'win_on_time':
      description = winner === "black" ? "Les Noirs ont gagné par dépassement de temps !" : "Les Blancs ont gagné par dépassement de temps !";
      break;
  }

  return (
    <div className="fixed inset-0 flex items-center justify-center bg-black/60 backdrop-blur-sm z-50">
      <div className="bg-white dark:bg-neutral-900 p-6 rounded-2xl shadow-2xl text-center max-w-sm w-full">
        <h2 className="text-2xl font-bold mb-4 text-gray-900 dark:text-gray-100">
          {result === "draw" ? "Partie Nulle !" :
           result === "timeout" ? "Temps écoulé !" :
           winner === "white" ? "Les Blancs ont gagné !" : "Les Noirs ont gagné !"}
        </h2>
        <p className="text-gray-700 dark:text-gray-300">{description}</p>
        <button
          onClick={onRestart}
          className="mt-4 px-6 py-2 rounded-xl bg-emerald-600 hover:bg-emerald-700 text-white font-semibold shadow-md transition-all"
        >
          Rejouer
        </button>
      </div>
    </div>
  );
}