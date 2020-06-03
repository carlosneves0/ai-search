import React, { useState, useEffect } from 'react'
import cloneDeep from 'lodash.clonedeep'
import Maze from './Maze'
import './MazeSolver.css'
import mazes from '../mazes'
import execlogs from '../execlogs'
const MAZE = 0
const ALGORITHM = 'a_star'
const THEME = 'monokai'
const FIRE_INTERVAL = 300

const initialMaze = mazes[MAZE]

export default function MazeSolver() {
  const [interval, _setInterval] = useState(null)
  const [maze, setMaze] = useState({
    data: initialMaze,
    at: initialSquare(initialMaze)
  })

  useEffect(() => {
    _setInterval(setInterval(
      () => handleNewEvent(fireNewEvent()),
      FIRE_INTERVAL
    ))
  }, [])

  useEffect(() => {
    document.title = algorithmPrettyName(ALGORITHM)
  }, [])

  function handleNewEvent(event) {
    // Update the maze according to each event type.
    // console.log(maze.data[1].join(''))
    switch (event.type) {
      case 'visit':
        return setMaze(prevMaze => visit(prevMaze, event.square))
      case 'succeed':
        return setMaze(prevMaze => succeed(prevMaze, event.path))
      case 'fail':
        return setMaze(prevMaze => fail(prevMaze, event.path))
      case 'halt':
        return clearInterval(interval)
    }
  }

  return (
    <div className={`MazeSolver MazeSolver-${THEME}`}>
      <Maze
        maze={maze.data}
        theme={THEME}
      />
    </div>
  )
}

function initialSquare(maze) {
  for (let i = 0; i < maze.length; i++) {
    for (let j = 0; j < maze[i].length; j++) {
      if (maze[i][j] === '#') {
        return [i, j]
      }
    }
  }
  throw new Error('Invalid maze has no initial square')
}

const execlog = execlogs[ALGORITHM][MAZE]
let offset = 0
function fireNewEvent() {
  if (offset < execlog.length) {
    return execlog[offset++]
  }
  return { type: 'halt' }
}

function visit(maze, next) {
  const newData = []
  for (const row of maze.data) {
    newData.push([...row])
  }
  newData[maze.at[0]][maze.at[1]] = '@'
  newData[next[0]][next[1]] = '#'
  console.log(newData[1])
  return {
    data: newData,
    at: next
  }
}

function succeed(maze, path) {
  const newMaze = cloneDeep(maze)
  for (const [i, j] of path) {
    newMaze.data[i][j] = '!'
  }
  return newMaze
}

function fail(maze, path) {
  const newMaze = cloneDeep(maze)
  // TODO: highlight path
  return newMaze
}

function algorithmPrettyName(algorithm) {
  switch (algorithm) {
    case 'depth_first_search':
      return 'Depth First Search'
    case 'breadth_first_search':
      return 'Breadth First Search'
    case 'best_first_search':
      return 'Best First Search'
    case 'a_star':
      return 'A*'
    case 'hill_climbing':
      return 'Hill Climbing'
    default:
      throw new Error(`Unknown algorithm "${algorithm}"`)
  }
}
