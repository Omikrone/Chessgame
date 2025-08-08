import React, { useEffect, useRef } from "react";
import { Chessground } from "@lichess-org/chessground";
import "@lichess-org/chessground/assets/chessground.base.css";
import "@lichess-org/chessground/assets/chessground.brown.css";
import "./pieces.css"; // notre CSS pour afficher les pièces

export default function App() {
  const boardRef = useRef(null);
  const cgRef = useRef(null);

  useEffect(() => {
    if (!boardRef.current) return;

    cgRef.current = Chessground(boardRef.current, {
      fen: "start",
      orientation: "white",
      movable: {
        free: true,
        showDests: true,
        color: "both",
      },
      events: {
        move: async (from, to) => {
          try {
            const response = await fetch("http://localhost:18080/game", {
              method: "POST",
              headers: {
                "Content-Type": "application/json"
              },
              body: JSON.stringify({
                from: from,
                to: to
              })
            });

            if (!response.ok) {
              throw new Error("Network error");
            }
            const data = await response.json();
            console.log("Server Response :", data);

          } catch (error) {
            console.log("Error :", error)
          }
        },
      },
    });

    return () => cgRef.current?.destroy();
  }, []);

  return (
    <div style={{ padding: 16 }}>
      <h3>Chessground avec pièces visibles</h3>
      <div ref={boardRef} style={{ width: 480, height: 480 }} />
    </div>
  );
}
