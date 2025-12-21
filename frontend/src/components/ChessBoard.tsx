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
  movable?: boolean;
};

export default function ChessBoard({ 
  onMove, 
  fen, 
  updateId, 
  orientation = "white",
  movable = true 
}: ChessBoardProps) {
  const boardRef = useRef<HTMLDivElement>(null);
  const cgRef = useRef<Api | null>(null);

  console.log("ChessBoard render - movable:", movable, "orientation:", orientation, "fen:", fen);

  useEffect(() => {
    if (!boardRef.current) return;

    const actualFen = fen === "start" ? "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" : fen;

    cgRef.current = Chessground(boardRef.current, {
      fen: actualFen,
      orientation,
      movable: {
        free: movable,
        color: movable ? orientation : undefined,
        events: movable ? {
          after: (from: string, to: string) => {
            console.log("ChessBoard: Move detected");
            const cg = cgRef.current;
            if (!cg) return;
            const piece = cg.state.pieces.get(to as Key);
            console.log("Piece moved:", {from, to, piece});
            onMove(from, to, piece ? piece.role : undefined);
          }
        } : undefined,
      },
      draggable: {
        enabled: movable
      },
      selectable: {
        enabled: movable
      }
    });

    return () => {
      cgRef.current?.destroy();
    };
  }, [orientation, onMove, movable]);

  useEffect(() => {
    if (cgRef.current) {
      const actualFen = fen === "start" ? "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" : fen;
      console.log("Updating Chessground FEN to:", actualFen);
      cgRef.current.set({ fen: actualFen });
    }
  }, [fen, updateId]);

  useEffect(() => {
    if (cgRef.current) {
      console.log("Updating Chessground movable to:", movable);
      cgRef.current.set({
        movable: {
          free: movable,
          color: movable ? orientation : undefined
        },
        draggable: {
          enabled: movable
        }
      });
    }
  }, [movable, orientation]);

  return <div ref={boardRef} style={{ width: 700, height: 700 }} />;
}