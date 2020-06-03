#!/usr/bin/env bash
set -uo pipefail

SEARCH_ALGORITHMS="${SEARCH_ALGORITHMS:-}"
if test -z "$SEARCH_ALGORITHMS"; then
  echo >&2 "Required env var \"SEARCH_ALGORITHMS\" hasn't been set"
  exit 1
fi

TIMESTAMP="${TIMESTAMP:-}"
if test -z "$TIMESTAMP"; then
  echo >&2 "Required env var \"TIMESTAMP\" hasn't been set"
  exit 1
fi

latest_timestamp=$(ls .execlogs | sort -r | head -1)

for algorithm in $SEARCH_ALGORITHMS; do
  for maze in $(ls __mazes__ | xargs basename --suffix .txt); do
    (echo; set -o xtrace
      diff \
        .execlogs/$latest_timestamp/$algorithm/$maze/stdout \
        .execlogs/$TIMESTAMP/$algorithm/$maze/stdout)
  done
done
