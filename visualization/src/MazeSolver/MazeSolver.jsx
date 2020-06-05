import React, { useState, useEffect } from 'react'
import cloneDeep from 'lodash.clonedeep'
import Maze from './Maze'
import './MazeSolver.css'
import mazes from '../mazes'
import execlogs from '../execlogs'
const ALGORITHMS = ['depth_first_search', 'breadth_first_search', 'best_first_search', 'a_star', 'hill_climbing']
const THEME = 'monokai'
const DEFAULT_MAZE_INDEX = 0
const DEFAULT_ALGORITHM = ALGORITHMS[0]
const DEFAULT_FIRE_INTERVAL = 20 // ms. Browsers appearently have a 4ms minimum interval.
let execlogOffset = 0
let execlogInterval = null

export default function MazeSolver() {
  const [mazeIndex, setMazeIndex] = useState(DEFAULT_MAZE_INDEX)
  const [algorithm, setAlgorithm] = useState(DEFAULT_ALGORITHM)
  const [fireInterval, setFireInterval] = useState(DEFAULT_FIRE_INTERVAL)
  const [maze, setMaze] = useState(initialMaze(mazes[mazeIndex]))
  const [execlog, setExeclog] = useState(execlogs[algorithm][mazeIndex])
  const [path, setPath] = useState(null)

  useEffect(() => {
    document.title = algorithmPrettyName(algorithm)
  }, [algorithm])

  function fireNewEvent() {
    if (execlogOffset < execlog.length) {
      return execlog[execlogOffset++]
    }
    return { type: 'halt' }
  }

  useEffect(() => {
    function handleNewEvent(event) {
      // Update the maze according to each event type.
      switch (event.type) {
        case 'visit':
          return setMaze(prevMaze => visit(prevMaze, event.square))
        case 'succeed':
          setMaze(prevMaze => succeed(prevMaze, event.path))
          setPath(event.path)
          return
        case 'fail':
          setMaze(prevMaze => fail(prevMaze, event.path))
          setPath(event.path)
          return
        case 'halt':
          clearInterval(execlogInterval)
          execlogInterval = null
          return
        default:
      }
    }
    execlogInterval = setInterval(
      () => handleNewEvent(fireNewEvent()),
      fireInterval
    )
    return () => {
      if (execlogInterval !== null) {
        clearInterval(execlogInterval)
      }
    }
  })

  useEffect(() => {
    clearInterval(execlogInterval)
    execlogOffset = 0
    setExeclog(execlogs[algorithm][mazeIndex])
    setMaze(initialMaze(mazes[mazeIndex]))
    setPath(null)
  }, [algorithm, mazeIndex])

  function handleSelectMazeIndex(event) {
    setMazeIndex(event.target.value)
  }

  function handleSelectAlgorithm(event) {
    setAlgorithm(event.target.value)
  }

  function handleFireIntervalChange(event) {
    setFireInterval(event.target.value)
  }

  return (
    <>
      <div className={`MazeSolver-Content MazeSolver-Content-${THEME}`}>
        <Maze
          maze={maze.data}
          theme={THEME}
        />
      </div>
      {path !== null && (
        <div className={`MazeSolver-PathLength`}>
          {path.length - 1}
        </div>
      )}
      <div className={`MazeSolver-Controls MazeSolver-Controls-${THEME}`}>
        <select
          value={mazeIndex}
          onChange={handleSelectMazeIndex}
        >
          {[0, 1, 2, 3, 4, 5, 6, 7, 8, 9].map(i => (
            <option key={i} value={i}>maze #{i}</option>
          ))}
        </select>
        <select
          value={algorithm}
          onChange={handleSelectAlgorithm}
        >
          {ALGORITHMS.map(a => (
            <option key={a} value={a}>{algorithmPrettyName(a)}</option>
          ))}
        </select>
        <input
          type='number'
          min={0}
          placeholder='interval'
          value={fireInterval}
          onChange={handleFireIntervalChange}
        />
      </div>
    </>
  )
}

function initialMaze(maze) {
  const data = cloneDeep(maze)
  let at = null
  for (let i = 0; i < data.length; i++) {
    for (let j = 0; j < data[i].length; j++) {
      if (data[i][j] === '#') {
        at = [i, j]
      } else if (data[i][j] === '@') {
        data[i][j] = '*'
      } else if (data[i][j] === '!') {
        data[i][j] = '*'
      } else if (data[i][j] === '_') {
        data[i][j] = '*'
      }
    }
  }
  if (at === null) {
    throw new Error('Invalid maze has no initial square')
  }
  return { data, at }
}

function visit(maze, next) {
  const newData = []
  for (const row of maze.data) {
    newData.push([...row])
  }
  newData[maze.at[0]][maze.at[1]] = '@'
  newData[next[0]][next[1]] = '#'
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
  for (const [i, j] of path) {
    newMaze.data[i][j] = '_'
  }
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
