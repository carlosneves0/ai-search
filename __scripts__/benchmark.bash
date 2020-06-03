#!/usr/bin/env bash
set -uo pipefail

SEARCH_ALGORITHMS="${SEARCH_ALGORITHMS:-}"
if test -z "$SEARCH_ALGORITHMS"; then
  echo >&2 "Required env var \"SEARCH_ALGORITHMS\" hasn't been set"
  exit 1
fi

N="${N:-}"
if test -z "$N"; then
  echo >&2 "Required env var \"N\" hasn't been set"
  exit 1
fi

##
# Benchmark **all** algorithms in **all** mazes.
#
echo "benchmark::n = $N"

mkdir -p .benchmark

timestamp=$(date '+%Y-%m-%d_%H:%M:%S.%N')
echo "benchmark::timestamp = \"$timestamp\""
mkdir .execlog/$timestamp

for algorithm in $SEARCH_ALGORITHMS; do
  mkdir -p .benchmark/$timestamp/$algorithm
  for maze in $(ls __mazes__ | xargs basename --suffix .txt); do
    mkdir -p .benchmark/$timestamp/$algorithm/$maze
    for i in $(seq $N); do
      echo
      echo "benchmark(algorithm = $algorithm, maze = $maze, i = $i) >>>"
      start=$(date +%s.%N)
      ./.bin/$algorithm < __mazes__/$maze.txt &> /dev/null
      exit_status=$?
      echo "$exit_status" > .benchmark/$timestamp/$algorithm/$maze/$i.xstatus
      seconds=$(awk "BEGIN { print $(date +%s.%N) - $start }")
      echo "$seconds" > .benchmark/$timestamp/$algorithm/$maze/$i.seconds
      echo "<<< returned ${exit_status} in ${seconds}s"
    done
  done
done

##
# Print whether the algorithm found a solution.
#
echo
echo "--- DID THE ALGORITHM FIND A SOLUTION? ---"
for algorithm in $(ls .benchmark/$timestamp); do
  for maze in $(ls .benchmark/$timestamp/$algorithm); do
    cp .benchmark/$timestamp/$algorithm/$maze/1.xstatus .benchmark/$timestamp/$algorithm/$maze/xstatus
    xstatus=$(cat .benchmark/$timestamp/$algorithm/$maze/xstatus)
    if test "$xstatus" == '0'; then
      echo "$algorithm in maze #$maze = YES"
    else
      echo "$algorithm in maze #$maze = NO"
    fi
  done
done

##
# Compute the average execution time for each algortihm in each maze.
#
echo
echo "--- AVERAGE TIMES (in seconds) ---"
for algorithm in $(ls .benchmark/$timestamp); do
  for maze in $(ls .benchmark/$timestamp/$algorithm); do
    sum=0.0
    for i in $(seq $N); do
      sum=$(awk "BEGIN { print $sum + $(cat .benchmark/$timestamp/$algorithm/$maze/$i.seconds) }")
    done
    average=$(awk "BEGIN { print $sum / $N }")
    echo "$average" > .benchmark/$timestamp/$algorithm/$maze/average
    echo "$algorithm in maze #$maze = ${average}s"
  done
done
