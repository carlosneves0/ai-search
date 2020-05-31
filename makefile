.DEFAULT_GOAL := build
.PHONY: build clean exec
.PRECIOUS: .bin/%.o .bin/graph/%.o

##
# `make build`
#
# Lists with the 5 search algorithms.
_SEARCH_ALGORITHMS := depth_first_search breadth_first_search \
	best_first_search a_star hill_climbing

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
#
clean:
	rm -rf .bin
	@rm -rf .execlog

##
# `make exec a=bfs m=0`
#
# Which algorithm to execute.
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

exec: .bin/$(_ALGORITHM)
ifndef m
	@exec .bin/$(_ALGORITHM)
else
	@exec .bin/$(_ALGORITHM) < __mazes__/$(m).txt
endif

## For debugging ##
##
# `make _execlog a=bfs m=0`
#
_TIMESTAMP := $(shell date '+%Y-%m-%d_%H:%M:%S.%N')
_execlog: .bin/$(_ALGORITHM)
	@mkdir -p .execlog
	@mkdir .execlog/$(_TIMESTAMP)
	@cp .bin/$(_ALGORITHM) .execlog/$(_TIMESTAMP)/$(_ALGORITHM).binary
ifndef m
	@cp __mazes__/0.txt .execlog/$(_TIMESTAMP)/stdin
else
	@cp __mazes__/$(m).txt .execlog/$(_TIMESTAMP)/stdin
endif
	@cd .execlog/$(_TIMESTAMP) && \
		./$(_ALGORITHM).binary \
			< stdin \
			> stdout \
			2> stderr; \
		echo $$? > exit_status
	@cat .execlog/$(_TIMESTAMP)/stdout
	@#echo vvv---+---+---stderr---+---+---vvv
	@#cat .execlog/$(_TIMESTAMP)/stderr

##
# `make benchmark n=1000`
#
##
# parameter `n`
# How many executions for each algorithm with each maze (default = 100).
ifndef n
_N := 100
else
_N := $(n)
endif

benchmark: build
	@# Benchmark all algorithms in all mazes.
	@echo 'benchmark::n = $(_N)'
	@rm -rf .benchmark; mkdir -p .benchmark
	@for algorithm in $(_SEARCH_ALGORITHMS); do \
		mkdir -p .benchmark/$$algorithm; \
		for maze in $(shell ls __mazes__ | xargs basename --suffix .txt); do \
			mkdir -p .benchmark/$$algorithm/$$maze; \
			for i in $$(seq $(_N)); do \
				echo "benchmark(algorithm = $$algorithm, maze = $$maze, i = $$i)"; \
				start=$$(date +%s.%N); \
				./.bin/$$algorithm < __mazes__/$$maze.txt &> /dev/null; \
				exit_status=$$?; \
				echo "$$exit_status" > .benchmark/$$algorithm/$$maze/$$i.exit_status; \
				seconds=$$(awk "BEGIN { print $$(date +%s.%N) - $$start }"); \
				echo "$$seconds" > .benchmark/$$algorithm/$$maze/$$i.seconds; \
				echo "<<< $${seconds}s"; \
			done \
		done \
	done

	@# Compute the average execution time for each algortihm in each maze.
	@echo "--- AVERAGE TIMES (in seconds) ---"
	@for a in $$(ls .benchmark); do \
		for m in $$(ls .benchmark/$$a); do \
			sum='0.0'; \
			for i in $$(seq $(_N)); do \
				sum=$$(awk "BEGIN { print $$sum + $$(cat .benchmark/$$a/$$m/$$i.seconds) }"); \
			done; \
			average=$$(awk "BEGIN { print $$sum / $(_N) }"); \
			echo "$$average" > .benchmark/$$a/$$m/average; \
			echo "$$a @ maze #$$m = $${average}s"; \
		done \
	done \
