const genmaze = require('generate-maze')
const MAZE_PATHWAY = '*'
const MAZE_OBSTACLE = '-'
const MAZE_SOURCE = '#'
const MAZE_TARGET = '$'

const NCOLUMNS = 8, NROWS = 16
const generatedMaze = genmaze(NCOLUMNS, NROWS)

const _asciiMaze = []
for (let i = 0, ii = 1; i < generatedMaze.length; i++, ii += 2) {
  for (let j = 0, jj = 1; j < generatedMaze[i].length; j++, jj += 2) {
    // middle
    asciiMaze(ii)[jj] = MAZE_PATHWAY
    // top
    asciiMaze(ii-1)[jj] = generatedMaze[i][j].top ? MAZE_OBSTACLE : MAZE_PATHWAY
    // right
    asciiMaze(ii)[jj+1] = generatedMaze[i][j].right ? MAZE_OBSTACLE : MAZE_PATHWAY
    // bottom
    asciiMaze(ii+1)[jj] = generatedMaze[i][j].bottom ? MAZE_OBSTACLE : MAZE_PATHWAY
    // left
    asciiMaze(ii)[jj-1] = generatedMaze[i][j].left ? MAZE_OBSTACLE : MAZE_PATHWAY
    // diagonals
    asciiMaze(ii-1)[jj-1] = MAZE_OBSTACLE
    asciiMaze(ii-1)[jj+1] = MAZE_OBSTACLE
    asciiMaze(ii+1)[jj-1] = MAZE_OBSTACLE
    asciiMaze(ii+1)[jj+1] = MAZE_OBSTACLE
  }
}

function asciiMaze(i) {
  if (!_asciiMaze[i]) {
    _asciiMaze[i] = []
  }
  return _asciiMaze[i]
}

// drop first and last lines
// drop first and last columns
const final = []
for (let i = 0; i < _asciiMaze.length; i++) {
  if (i === 0 || i === _asciiMaze.length - 1) {
    continue
  }
  for (let j = 0; j < _asciiMaze[i].length; j++) {
    if (j === 0 || j === _asciiMaze[i].length - 1) {
      continue
    }
    if (!final[i-1]) final[i-1] = []
    final[i-1][j-1] = _asciiMaze[i][j]
  }
}

process.stdout.write(`${final.length} ${final[0].length}\n`)
process.stdout.write(final.map(line => line.join('')).join('\n') + '\n')
// console.log(generatedMaze[0][0])
// console.log(generatedMaze[0][1])
// console.log(generatedMaze[1][0])
// console.log(generatedMaze[1][1])
