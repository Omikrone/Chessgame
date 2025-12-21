import { useEffect, useRef } from "react";
import { Chessground } from "@lichess-org/chessground";
import { Chess } from "chess.js";
import "@lichess-org/chessground/assets/chessground.base.css";
import type { Api } from "@lichess-org/chessground/api";
import type { Key } from "@lichess-org/chessground/types";

type ChessBoardProps = {
  onMove: (from: string, to: string, piece?: string) => void;
  orientation?: "white" | "black";
  fen: string;
  updateId: number;
};

export default function ChessBoard({ 
  onMove, 
  fen, 
  updateId, 
  orientation = "white",
}: ChessBoardProps) {
  const boardRef = useRef<HTMLDivElement>(null);
  const cgRef = useRef<Api | null>(null);

  const onMoveRef = useRef(onMove);

  useEffect(() => {
    onMoveRef.current = onMove;
  }, [onMove]);

  const getDests = (fen: string) => {
    try {
        const chess = new Chess(fen === "start" ? undefined : fen);
        const dests = new Map<Key, Key[]>();
        
        chess.moves({ verbose: true }).forEach((move) => {
          const from = move.from as Key;
          const to = move.to as Key;
          if (!dests.has(from)) dests.set(from, []);
          dests.get(from)?.push(to);
        });
        
        return dests;
    } catch (e) {
        console.error("Invalid FEN:", fen);
        return new Map();
    }
  };

  useEffect(() => {
    if (!boardRef.current) return;

    const actualFen = fen === "start" ? "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" : fen;
    const dests = getDests(actualFen);

    cgRef.current = Chessground(boardRef.current, {
      fen: actualFen,
      orientation,
      movable: {
        free: false,
        color: orientation,
        dests: dests,
        showDests: true,
        events: {
          after: (from: string, to: string) => {
             const piece = cgRef.current?.state.pieces.get(to as Key);
             onMoveRef.current(from, to, piece?.role);
          }
        },
      },
      draggable: {
        enabled: true,
        showGhost: true
      },
      selectable: {
        enabled: true
      },
      highlight: {
        lastMove: true,
        check: true
      }
    });

    return () => {
      cgRef.current?.destroy();
    };
  }, []); 

  useEffect(() => {
    if (cgRef.current) {
      const actualFen = fen === "start" ? "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" : fen;

      const dests = getDests(actualFen);

      const chess = new Chess(actualFen);
      const turnColor = chess.turn() === 'w' ? 'white' : 'black';

      cgRef.current.set({ 
        fen: actualFen,
        turnColor: turnColor,
        movable: {
            dests: dests, 
            color: orientation,
            events: {
              after: (from: string, to: string) => {
                 const piece = cgRef.current?.state.pieces.get(to as Key);
                 onMoveRef.current(from, to, piece?.role);
              }
            }
        },
        check: chess.inCheck()
      });
    }
  }, [fen, updateId, orientation]);

  useEffect(() => {
    if (cgRef.current) {
        cgRef.current.set({ orientation });
    }
  }, [orientation]);

  return <div ref={boardRef} style={{ width: 700, height: 700 }} />;
}