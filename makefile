.DEFAULT_GOAL := build
.PHONY: build clean exec benchmark visualization execlogs mazes2js execlogs2js
.PRECIOUS: .bin/%.o .bin/graph/%.o

##
# `make build`
# Compile all 5 binaries.
##
_SEARCH_ALGORITHMS := depth_first_search breadth_first_search best_first_search a_star hill_climbing

build: $(addprefix .bin/, $(_SEARCH_ALGORITHMS))

.bin/%: .bin/%.o .bin/maze.o .bin/graph.o .bin/graph/node.o .bin/graph/path.o | .bin
	g++ -std=c++11 -Wall $(<) .bin/maze.o .bin/graph.o .bin/graph/node.o .bin/graph/path.o -o $(@)

.bin/%.o: %/main.cpp | .bin
	g++ -c -std=c++11 -Wall $(<) -o $(@)

.bin/maze.o: maze/maze.cpp maze/maze.hpp | .bin
	g++ -c -std=c++11 -Wall $(<) -o $(@)

.bin/graph.o: graph/graph.cpp graph/graph.hpp | .bin
	g++ -c -std=c++11 -Wall $(<) -o $(@)

.bin/graph/%.o: graph/%.cpp graph/graph.hpp | .bin/graph
	g++ -c -std=c++11 -Wall $(<) -o $(@)

.bin/graph: | .bin
	mkdir -p .bin/graph

.bin:
	mkdir -p .bin

##
# `make clean`
##
clean:
	rm -rf .bin

##
# `make exec a=bfs m=0`
# Execute one binary and optionally pass one maze as input.
##

# Parameter `a`: which algorithm to execute.
ifndef a
_ALGORITHM := depth_first_search
else ifeq '$(a)' 'dfs'
_ALGORITHM := depth_first_search
else ifeq '$(a)' 'bfs'
_ALGORITHM := breadth_first_search
else ifeq '$(a)' 'bsfs'
_ALGORITHM := best_first_search
else ifeq '$(a)' 'as'
_ALGORITHM := a_star
else ifeq '$(a)' 'hc'
_ALGORITHM := hill_climbing
else
_ALGORITHM := $(a)
endif

# Parameter `m`: the index of the maze to pass as input.
ifndef m
	_MAZE :=
else
	_MAZE := $(m)
endif

exec: .bin/$(_ALGORITHM)
	-@test '$(_MAZE)' == '' \
		&& exec .bin/$(_ALGORITHM) 2> /dev/null \
		|| exec .bin/$(_ALGORITHM) < __mazes__/$(_MAZE).txt 2> /dev/null

##
# `make benchmark n=1000`
# Execute each algorithm n times in each maze. Compute the average response times.
##

# Parameter `n`
# How many executions for each algorithm in each maze (default = 100).
ifndef n
_N := 100
else
_N := $(n)
endif

benchmark: build
	@export SEARCH_ALGORITHMS='$(_SEARCH_ALGORITHMS)' && \
		export N='$(_N)' && \
		bash __scripts__/benchmark.bash

##
# `make visualization`
# Start the visualization frontend.
##
visualization: mazes2js execlogs2js
	@cd visualization && yarn start

##
# `make execlogs`
# Generate and persist the execution logs for each algorithm in each maze.
##
execlogs: build
	@export SEARCH_ALGORITHMS='$(_SEARCH_ALGORITHMS)' && \
		bash __scripts__/execlogs.bash

##
# `make mazes2js`
# Convert each maze to a Javascript representation.
##
mazes2js:
	@node __scripts__/mazes2js.js

##
# `make execlogs2js`
# Convert execlogs to a Javascript representation (**only the latest timestamp**).
##
execlogs2js: execlogs
	@node __scripts__/execlogs2js.js

_diff:
	@export SEARCH_ALGORITHMS='$(_SEARCH_ALGORITHMS)' && \
		export TIMESTAMP='$(t)' && \
		bash __scripts__/.diff.bash
