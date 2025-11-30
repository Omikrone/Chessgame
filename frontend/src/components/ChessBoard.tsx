import { useEffect, useRef } from "react";
import { Chessground } from "@lichess-org/chessground";
import "@lichess-org/chessground/assets/chessground.base.css";
import type { Api } from "@lichess-org/chessground/api";
import type { Key } from "@lichess-org/chessground/types";


type ChessBoardProps = {
  onMove: (from: string, to: string, piece?: string) => void;
  orientation?: "white" | "black";
  fen: string;
  updateId: number;
};

export default function ChessBoard({ onMove, fen, updateId, orientation = "white" }: ChessBoardProps) {
  const boardRef = useRef<HTMLDivElement>(null);
  const cgRef = useRef<Api | null>(null);

  useEffect(() => {
    if (!boardRef.current) return;

    cgRef.current = Chessground(boardRef.current, {
      fen,
      orientation,
      movable: {
        free: true,
        events: {
          after: (from: string, to: string) => {
            const cg = cgRef.current;
            if (!cg) return;
            const piece = cg.state.pieces.get(to as Key);
            console.log("Piece moved:", {from, to, piece});
            onMove(from, to, piece ? piece.role : undefined);
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