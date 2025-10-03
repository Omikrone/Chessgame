import { useEffect, useRef } from "react";
import { Chessground } from "@lichess-org/chessground";
import "@lichess-org/chessground/assets/chessground.base.css";


type ChessBoardProps = {
  onMove: (from: string, to: string) => void;
  orientation?: "white" | "black";
  fen: string;
  updateId: number;
};

export default function ChessBoard({ onMove, fen, updateId, orientation = "white" }: ChessBoardProps) {
  const boardRef = useRef<HTMLDivElement>(null);
  const cgRef = useRef<any>(null);

  useEffect(() => {
    if (!boardRef.current) return;

    cgRef.current = Chessground(boardRef.current, {
      fen,
      orientation,
      movable: {
        free: true,
        events: {
          after: (from: string, to: string) => {
            console.log("MOVE PLAYED!");
            onMove(from, to);
          }
        },
      },
    });

    return () => {
      cgRef.current?.destroy();
    };
  }, [orientation, onMove]);

  useEffect(() => {
    if (cgRef.current) {
      cgRef.current.set({ fen });
    }
  }, [fen, updateId]);

  return <div ref={boardRef} style={{ width: 700, height: 700 }} />;
}