import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import GamePage from "./pages/GamePage";
import HomePage from './pages/HomePage';


export default function App() {
    return (
        <Router>
            <Routes>
                <Route path="/" element={<HomePage />} />
                <Route path="/games/:gameId" element={<GamePage />} />
            </Routes>
        </Router>
    )
}