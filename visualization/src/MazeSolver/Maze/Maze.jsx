import React from 'react'
import './Maze.css'

export default function Maze({ maze, theme }) {
  // const vh = Math.max(document.documentElement.clientHeight || 0, window.innerHeight || 0);
  // let squareSide = `calc(100vh / ${maze.m})`
  // if (maze.m > maze.n) {
  //   squareSide = `calc(100vw / ${maze.n})`
  // }
  //  squareSide={squareSide}
  return (
    <div className='Maze'>
      {maze.map(row => (
        <MazeRow row={row} theme={theme} />
      ))}
    </div>
  )
}

function MazeRow({ row, squareSide, theme }) {
  return (
    <div className='MazeRow'>
      {row.map(square => (
        <MazeSquare
          data={square}
          side={squareSide}
          theme={theme}
        />
      ))}
    </div>
  )
}

function MazeSquare({ data, side, theme }) {
  const MAZE_OUTTER_WALL = '~'
  const MAZE_PATHWAY = '*'
  const MAZE_VISITED = '@'
  const MAZE_OBSTACLE = '-'
  const MAZE_CURRENT = '#'
  const MAZE_TARGET = '$'

  switch (data) {
    case MAZE_OUTTER_WALL:
      return <span className={`MazeSquare MazeSquare-OutterWall-${theme}`} />
    case MAZE_PATHWAY:
      return <span className={`MazeSquare MazeSquare-Pathway-${theme}`} />
    case MAZE_VISITED:
      return <span className={`MazeSquare MazeSquare-Visited-${theme}`} />
    case MAZE_OBSTACLE:
      return <span className={`MazeSquare MazeSquare-Obstacle-${theme}`} />
    case MAZE_CURRENT:
      return <span className={`MazeSquare MazeSquare-Current-${theme}`} />
    case MAZE_TARGET:
      return <span className={`MazeSquare MazeSquare-Target-${theme}`} />
    default:
      return null
  }
}
