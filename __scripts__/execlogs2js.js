const { resolve: presolve } = require('path')
const { spawnSync, execSync } = require('child_process')
const { readFileSync: fread, writeFileSync: fwrite } = require('fs')

main()

function main() {
  try {
    const PKG_ROOT = presolve(`${__dirname}/..`)
    const LATEST_TIMESTAMP = exec(`ls ${PKG_ROOT}/.execlogs | sort -r | head -1`)[0]
    const SRC = presolve(`${PKG_ROOT}/.execlogs/${LATEST_TIMESTAMP}`)
    const ART = presolve(`${PKG_ROOT}/visualization/src/execlogs.json`)

    spawn('rm', ['-f', ART])

    const execlogs = {}
    for (const algorithm of spawn('ls', [SRC])) {
      execlogs[algorithm] = {}
      for (const mazeIndex of spawn(
        'ls',
        [`${SRC}/${algorithm}`]
      ).filter(s => s !== 'binary')) {
        execlogs[algorithm][mazeIndex] = parseExeclog(
          fread(`${SRC}/${algorithm}/${mazeIndex}/stderr`, 'utf8')
        )
      }
    }

    fwrite(ART, JSON.stringify(execlogs))
  } catch (error) {
    console.error(error)
    process.exit(1)
  }
}

function spawn(cmd, args) {
  return spawnSync(cmd, args).stdout.toString('utf8').trim().split('\n')
}

function exec(cmdline) {
  return execSync(cmdline).toString('utf8').trim().split('\n')
}

function parseExeclog(execlog) {
  return execlog
    .split('\n')
    .filter(Boolean)
    .map(
      line => line.split(' ')
    )
    .map(
      ([type, payload]) => {
        switch (type) {
          case 'visit':
            return { type, square: addPadding(JSON.parse(payload)) }
          case 'succeed':
          case 'fail':
            return { type, path: JSON.parse(payload).map(addPadding) }
          default:
            throw new Error(`Unknown event type "${type}"`)
        }
      }
    )
}

// Add outter wall padding.
function addPadding([i, j]) {
  return [i+1, j+1]
}
