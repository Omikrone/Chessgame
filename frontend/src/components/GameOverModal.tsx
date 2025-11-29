type GameOverModalProps = {
    result: "checkmate" | "draw" | "stalemate" | "timeout";
    winner: "white" | "black" | null;
    onRestart: () => void;
}


export default function GameOverModal({ result, winner, onRestart }: GameOverModalProps) {
  if (!winner && result !== "draw" && result !== "stalemate" && result !== "timeout") return null;

  let message = "";
  switch (result) {
    case "checkmate":
      message = winner === "black" ? "Les Noirs ont gagné par échec et mat !" : "Les Blancs ont gagné par échec et mat !";
      break;
    case "draw":
      message = "Match nul !";
      break;
    case "stalemate":
      message = "Match nul par pat !";
      break;
    case "timeout":
      message = winner === "black" ? "Les Noirs ont gagné par dépassement de temps !" : "Les Blancs ont gagné par dépassement de temps !";
      break;
  }

  return (
    <div className="fixed inset-0 flex items-center justify-center bg-black/60 backdrop-blur-sm z-50">
      <div className="bg-white dark:bg-neutral-900 p-6 rounded-2xl shadow-2xl text-center max-w-sm w-full">
        <h2 className="text-2xl font-bold mb-4 text-gray-900 dark:text-gray-100">
          {result === "draw" || result === "stalemate"
            ? "Match nul !"
            : winner === "black"
            ? "Les Noirs ont gagné !"
            : "Les Blancs ont gagné !"}
        </h2>
        <p className="text-gray-700 dark:text-gray-300">{message}</p>
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