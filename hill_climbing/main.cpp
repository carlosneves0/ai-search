#define __HILL_CLIMBING__
#include <iostream>
#include <cmath>
#include <queue>
#include "../maze/maze.hpp"
#include "../graph/graph.hpp"
typedef unsigned int uint;

/* Global maze instance */
maze* maze_instance = nullptr;

/** Objective function f(x)
 * f(x) is the linear distance from x to target.
 */
double f(graph::node& x)
{
	static maze::position target = (*maze_instance).target();
	uint xi = x.i(), xj = x.j(), ti = target.i, tj = target.j;
	return std::sqrt(std::pow((double) ti - xi, 2.0) + std::pow((double) tj - xj, 2.0));
}

int main()
{
	/* Read and convert stdin into meaningful data structures. */
	maze maze(std::cin); maze_instance = &maze;
	graph graph(maze);
	graph::node source = graph.source();
	graph::node target = graph.target();

	/** Hill Climbing Search Algorithm
	 * Hill Climbing optimization problem: minimize objective function f(x).
	 * NOTE: hill climbing finds a local minimum.
	 */
	graph::path solution(source);
	graph::node current = source;
	while (true)
	{
		graph.visit(current);

		graph::node next = current;
		for (graph::node& neighbor : graph.adjacent_nodes(current))
			if (f(neighbor) <= f(next))
				next = neighbor;

		if (next == current)
			break;
		else
			solution.add_node(current = next);
	}

	if (solution.last_node() == target)
	{
		std::cout << solution << "\n";
		return 0;
	}

	std::cout << "No solutions were found for this maze.\n";
	return 1;
}

/* Cost function g(x) (UNUSED IN THIS CODE; SAFE TO IGNORE) */
double g(graph::node& x)
{
	return 0.0;
}

/* Heuristic function h(x) (UNUSED IN THIS CODE; SAFE TO IGNORE) */
double h(graph::node& x)
{
	return 0.0;
}
