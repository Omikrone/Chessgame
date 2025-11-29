type PromotionModalProps = {
  color: 'white' | 'black';
  onSelect: (piece: 'q' | 'r' | 'b' | 'n') => void;
}

export default function PromotionModal({ color, onSelect }: PromotionModalProps) {
  const pieces = [
    { type: 'q' as const, label: 'Dame' },
    { type: 'r' as const, label: 'Tour' },
    { type: 'b' as const, label: 'Fou' },
    { type: 'n' as const, label: 'Cavalier' }
  ];

  return (
    <div className="fixed inset-0 flex items-center justify-center bg-black/60 backdrop-blur-sm z-50">
      <div className="bg-white dark:bg-neutral-900 p-6 rounded-2xl shadow-2xl text-center max-w-sm w-full">
        <h2 className="text-2xl font-bold mb-6 text-gray-900 dark:text-gray-100">
          Promotion du pion
        </h2>
        <p className="text-gray-700 dark:text-gray-300 mb-6">
          Choisissez la pièce de promotion
        </p>
        
        <div className="grid grid-cols-2 gap-4 mb-6">
          {pieces.map((piece) => (
            <button
              key={piece.type}
              onClick={() => onSelect(piece.type)}
              className="flex flex-col items-center p-4 rounded-xl bg-beige-light hover:bg-beige-default dark:bg-brown-medium dark:hover:bg-brown-light transition-all duration-200 group"
            >
              <div 
                className={`w-16 h-16 piece ${piece.type}.${color} bg-cover bg-no-repeat`}
                style={{ backgroundImage: `var(--piece-${color}-${piece.type})` }}
              />
              <span className="mt-2 text-sm font-medium text-brown-dark dark:text-beige-light group-hover:text-brown-medium">
                {piece.label}
              </span>
            </button>
          ))}
        </div>

        <div className="text-xs text-gray-500 dark:text-gray-400">
          Le pion sera transformé en la pièce sélectionnée
        </div>
      </div>
    </div>
  );
}