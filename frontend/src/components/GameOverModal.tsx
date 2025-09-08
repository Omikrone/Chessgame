type GameOverModalProps = {
    result: "checkmate" | "draw";
    winner: "white" | "black" | null;
    onRestart: () => void;
}


export default function GameOverModal({ result, winner, onRestart }: GameOverModalProps) {
  if (!winner && result !== "draw") return null;

  return (
    <div className="fixed inset-0 flex items-center justify-center bg-black/60 backdrop-blur-sm z-50">
      <div className="bg-white dark:bg-neutral-900 p-6 rounded-2xl shadow-2xl text-center max-w-sm w-full">
        <h2 className="text-2xl font-bold mb-4 text-gray-900 dark:text-gray-100">
          {result === "draw"
            ? "Match nul !"
            : winner === "black"
            ? "Les Noirs ont gagné !"
            : "Les Blancs ont gagné !"}
        </h2>
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