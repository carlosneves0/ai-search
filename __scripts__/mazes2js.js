const { resolve: presolve } = require('path')
const { spawnSync } = require('child_process')
const { readFileSync: fread, writeFileSync: fwrite } = require('fs')
const PKG_ROOT = presolve(`${__dirname}/..`)
const SRC = presolve(`${PKG_ROOT}/__mazes__`)
const ART = presolve(`${PKG_ROOT}/visualization/src/mazes`)

main()

function main() {
  try {
    const mazeTxts = spawn('ls', [SRC]).split('\n')
    spawn('rm', ['-rf', ART])
    spawn('mkdir', ['-p', ART])

    for (mazeTxt of mazeTxts) {
      const mazeIndex = parseInt(mazeTxt.split('.txt')[0], 10)
      const mazeData = fread(`${SRC}/${mazeTxt}`, 'utf8')
      const [line0, ...lines] = mazeData.split('\n')
      const m = parseInt(line0.split(' ')[0], 10)
      const n = parseInt(line0.split(' ')[1], 10)
      const data = addOutterWall({ n, lines: lines.filter(Boolean) })
      const mazeJs = `export default ${JSON.stringify(data.map(l => l.split(''))).replace(/"/g, '\'')}
`
      fwrite(`${ART}/${mazeIndex}.js`, mazeJs)
    }

    const indexJs = `${mazeTxts.map((_, index) => `import maze${index} from './${index}'`).join('\n')}
export default [${mazeTxts.map((_, index) => `maze${index}`).join(', ')}]
`
    fwrite(`${ART}/index.js`, indexJs)
  } catch (error) {
    console.error(error)
    process.exit(1)
  }
}

function spawn(cmd, args) {
  return spawnSync(cmd, args).stdout.toString('utf8').trim()
}

function addOutterWall({ n, lines }) {
  newData = ['~'.repeat(n + 2)]
  for (line of lines) {
    newData.push(['~', ...line, '~'].join(''))
  }
  newData.push('~'.repeat(n + 2))
  return newData
}
