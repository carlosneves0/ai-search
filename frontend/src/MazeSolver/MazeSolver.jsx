import React from 'react'
import Maze from './Maze'
import './MazeSolver.css'

export default function MazeSolver() {
  const UI_THEMES = ['monokai', '?']

  const theme = UI_THEMES[0]

  return (
    <div className={`MazeSolver MazeSolver-${theme}`}>
      <Maze theme={theme} />
    </div>
  )
}
