import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './chess.css'
import GamePage from './pages/GamePage.js'

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <GamePage gameId='1234' />
  </StrictMode>,
)
