import { Github } from "lucide-react";

export default function GithubButton() {
  return (
    <a
      href="https://github.com/Omikrone/Chessgame"
      target="_blank"
      rel="noopener noreferrer"
      className="absolute top-4 right-4 inline-flex items-center gap-2 px-4 py-2 rounded-xl bg-gray-900 text-white hover:bg-gray-800 transition-colors shadow-md"
    >
      <Github size={20} />
      <span>Voir sur GitHub</span>
    </a>
  );
}
