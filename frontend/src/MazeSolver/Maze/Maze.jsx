import React, { useState } from 'react'
import maze0 from './mazes/0'
import './Maze.css'

export default function Maze({ theme }) {
  const [maze] = useState(maze0)
  const vh = Math.max(document.documentElement.clientHeight || 0, window.innerHeight || 0);
  const squareSide = `calc(100vh / ${maze.m})`

  const style = {
    margin: '0 auto',
    width: 'fit-content'
  }

  return (
    <div style={style}>
      {maze.data.map(line => (
        <div style={{ height: squareSide }}>
          {line.split('').map(squareData => (
            <MazeSquare
              data={squareData}
              side={squareSide}
              theme={theme}
            />
          ))}
        </div>
        )
      )}
    </div>
  )
}

// maze.data
function MazeSquare({ data, side, theme }) {
  const MAZE_OUTTER_WALL = '~'
  const MAZE_PATHWAY = '*'
  const MAZE_VISITED_PATHWAY = '@'
  const MAZE_OBSTACLE = '-'
  const MAZE_CURRENT = '#'
  const MAZE_TARGET = '$'

  const style = {
    height: side,
    width: side,
    display: 'inline-block'
  }

  switch (data) {
    case MAZE_OUTTER_WALL:
      return (
        <span
          className={`MazeSquare-OutterWall-${theme}`}
          style={style}
        />
      )
    case MAZE_PATHWAY:
      return (
        <span
          className={`MazeSquare-Pathway-${theme}`}
          style={style}
        />
      )
    case MAZE_VISITED_PATHWAY:
      return (
        <span
          className={`MazeSquare-VisitedPathway-${theme}`}
          style={style}
        />
      )
    case MAZE_OBSTACLE:
      return (
        <span
          className={`MazeSquare-Obstacle-${theme}`}
          style={style}
        />
      )
    case MAZE_CURRENT:
      return (
        <span
          className={`MazeSquare-Current-${theme}`}
          style={style}
        />
      )
    case MAZE_TARGET:
      return (
        <span
          className={`MazeSquare-Target-${theme}`}
          style={style}
        />
      )
    default:
      return null
  }
}
