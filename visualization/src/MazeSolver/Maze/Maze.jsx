import React, { useState, useRef, useEffect } from 'react'
import './Maze.css'

export default function Maze({ maze, theme }) {
  const [dim, setDim] = useState(null)
  const mazeContentRef = useRef(null)

  const m = maze.length
  const n = maze[0].length

  let squareSide = 0
  if (dim) {
    squareSide = Math.min(dim.height / (m+1), dim.width / (n+4))
  }
  squareSide = `${squareSide}px`

  useEffect(() => {
    if (mazeContentRef) {
      setDim({ width: mazeContentRef.current.offsetWidth, height: mazeContentRef.current.offsetHeight })
    }
  }, [mazeContentRef])

  return (
    <div
      className='MazeContainer'
      ref={mazeContentRef}
    >
      <div>
        {maze.map((row, index) => (
          <div key={index} style={{ height: squareSide }}>
            {row.map((square, index) => (
              <MazeSquare
                key={index}
                data={square}
                side={squareSide}
                theme={theme}
              />
            ))}
          </div>
        ))}
      </div>
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
  const MAZE_HIGHLIGHT = '!'
  const MAZE_LOWLIGHT = '_'

  switch (data) {
    case MAZE_OUTTER_WALL:
      return (
        <span
          className={`MazeSquare MazeSquare-OutterWall-${theme}`}
          style={{ width: side, height: side }}
        />
      )
    case MAZE_PATHWAY:
      return (
        <span
          className={`MazeSquare MazeSquare-Pathway-${theme}`}
          style={{ width: side, height: side }}
        />
      )
    case MAZE_VISITED:
      return (
        <span
          className={`MazeSquare MazeSquare-Visited-${theme}`}
          style={{ width: side, height: side }}
        />
      )
    case MAZE_OBSTACLE:
      return (
        <span
          className={`MazeSquare MazeSquare-Obstacle-${theme}`}
          style={{ width: side, height: side }}
        />
      )
    case MAZE_CURRENT:
      return (
        <span
          className={`MazeSquare MazeSquare-Current-${theme}`}
          style={{ width: side, height: side }}
        />
      )
    case MAZE_TARGET:
      return (
        <span
          className={`MazeSquare MazeSquare-Target-${theme}`}
          style={{ width: side, height: side }}
        />
      )
    case MAZE_HIGHLIGHT:
      return (
        <span
          className={`MazeSquare MazeSquare-Highlight-${theme}`}
          style={{ width: side, height: side }}
        />
      )
    case MAZE_LOWLIGHT:
      return (
        <span
          className={`MazeSquare MazeSquare-Lowlight-${theme}`}
          style={{ width: side, height: side }}
        />
      )
    default:
      return null
  }
}
