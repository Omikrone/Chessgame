import { useEffect, useRef } from "react";
import { Chessground } from "@lichess-org/chessground";
import "@lichess-org/chessground/assets/chessground.base.css";


type ChessBoardProps = {
  onMove: (from: string, to: string) => void;
  fen: string;
};

export default function ChessBoard({ onMove, fen }: ChessBoardProps) {
  const boardRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    if (!boardRef.current) return;

    const cg = Chessground(boardRef.current, {
      fen,
      movable: {
        free: true,
        color: "white",
        events: {
          after: (from: string, to: string) => onMove(from, to),
        },
      },
    });

    return () => {
      cg.destroy();
    };
  }, [fen, onMove]);

  return <div ref={boardRef} style={{ width: 400, height: 400 }} />;
}