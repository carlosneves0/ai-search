#define __BEST_FIRST_SEARCH__
#include <iostream>
#include <cmath>
#include <queue>
#include "../maze/maze.hpp"
#include "../graph/graph.hpp"
typedef unsigned int uint;

/* Global maze instance */
maze* maze_instance = nullptr;

/* Cost function g(x) */
double g(graph::node& x)
{
	return 0.0;
}

/** Heuristic function h(x)
 * h(x) is the linear distance from x to target.
 */
double h(graph::node& x)
{
	static maze::position target = (*maze_instance).target();
	uint ti = target.i, tj = target.j, xi = x.i(), xj = x.j();
	return std::sqrt(std::pow((double) ti - xi, 2.0) + std::pow((double) tj - xj, 2.0));
}

int main()
{
	/* Read and convert stdin into meaningful data structures. */
	maze maze(std::cin); maze_instance = &maze;
	graph graph(maze);
	graph::node source = graph.source();
	graph::node target = graph.target();

	/* Greedy Best First Search Algorithm */
	std::priority_queue<graph::path> L;
	graph::path initial_path(source); L.push(initial_path);

	while (!L.empty())
	{
		graph::path p = L.top(); L.pop();
		graph::node x = p.last_node();

		if (!graph.was_visited(x))
		{
			graph.visit(x);

			if (x == target)
			{
				std::cout << p << "\n";
				return 0;
			}

			for (graph::node& y : graph.adjacent_nodes(x))
				if (!graph.was_visited(y))
				{
					graph::path new_path(p, y);
					L.push(new_path);
				}
		}
	}

	std::cout << "No solutions were found for this maze.\n";
	return 1;
}
