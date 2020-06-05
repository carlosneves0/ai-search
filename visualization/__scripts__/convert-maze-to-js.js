const { resolve } = require('path')
const { spawnSync: spawn } = require('child_process')
// const spawn = require('spawna')
const { readFileSync: fread, writeFileSync: fwrite } = require('fs')
const PKG_ROOT = resolve(`${__dirname}/..`)

main()
  // .catch(e => {
  //   console.error(e)
  //   process.exit(1)
  // })

function main() {
  console.log(spawn('ls', [`${PKG_ROOT}/.__mazes__`]))
  // const mazeTxts = (await spawn('ls', [`${PKG_ROOT}/.__mazes__`])).stdout.split('\n')
  // await spawn('rm', ['-rf', `${PKG_ROOT}/mazes`])
  // await spawn('mkdir', ['-p', `${PKG_ROOT}/mazes`])
  // for (mazeTxt of mazeTxts) {
  //   const index = parseInt(mazeTxt.split('.txt')[0], 10)
  //   const mazeData = fread(`${PKG_ROOT}/.__mazes__/${mazeTxt}`, 'utf8')
  //   const [line0, ...lines] = mazeData.split('\n')
  //   const m = parseInt(line0.split(' ')[0], 10)
  //   const n = parseInt(line0.split(' ')[1], 10)
  //   const data = addOutterWall({ n, lines: lines.filter(Boolean) })
  //   const mazeJs = `
  //     export default {
  //       m: ${m + 2},
  //       n: ${n + 2},
  //       data: ${JSON.stringify(data, null, 2).replace(/"/g, '\'')}
  //     }
  //   `
  //   fwrite(`${PKG_ROOT}/mazes/${index}.js`, mazeJs)
  // }
}

function addOutterWall({ n, lines }) {
  newData = ['~'.repeat(n + 2)]
  for (line of lines) {
    newData.push(['~', ...line, '~'].join(''))
  }
  newData.push('~'.repeat(n + 2))
  return newData
}
