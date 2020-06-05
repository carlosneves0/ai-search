#!/usr/bin/env bash
set -uo pipefail

SEARCH_ALGORITHMS="${SEARCH_ALGORITHMS:-}"
if test -z "$SEARCH_ALGORITHMS"; then
  echo >&2 "Required env var \"SEARCH_ALGORITHMS\" hasn't been set"
  exit 1
fi

timestamp=$(date '+%Y-%m-%d_%H:%M:%S.%N')

mkdir -p .execlogs/$timestamp

for algorithm in $SEARCH_ALGORITHMS; do
  mkdir -p .execlogs/$timestamp/$algorithm
  cp .bin/$algorithm .execlogs/$timestamp/$algorithm/binary
  for maze in $(ls __mazes__ | xargs basename --suffix .txt); do
    mkdir -p .execlogs/$timestamp/$algorithm/$maze
    cp __mazes__/$maze.txt .execlogs/$timestamp/$algorithm/$maze/stdin
    (cd .execlogs/$timestamp/$algorithm
      ./binary < $maze/stdin > $maze/stdout 2> $maze/stderr
      echo $? > $maze/xstatus)
  done
done
