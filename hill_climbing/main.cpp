#define __HILL_CLIMBING__
#include <iostream>
#include <cmath>
#include <queue>
#include "../maze/maze.hpp"
#include "../graph/graph.hpp"
typedef unsigned int uint;

maze* maze_instance = nullptr;

// Objective function: cartesian distance to target maze position.
// Optimization problem: minimize h(x).
// NOTE: hill climbing finds a local minimum.
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

	/* Hill Climbing Search Algorithm */
	graph::path solution(source);
	graph::node current = source;
	while (true)
	{
		graph::node next = current;
		for (graph::node& neighbor : graph.adjacent_nodes(current))
			if (f(neighbor) <= f(next))
				next = neighbor;

		if (next == current)
			break;
		else
			solution.add_node(current = next);
	}

	std::cout << solution << "\n";

	return 0;
}

// These functions are here so the linker can link the graph::path class.
double g(graph::node& x)
{
	return 0.0;
}
double h(graph::node& x)
{
	return 0.0;
}
