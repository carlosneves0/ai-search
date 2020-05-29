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
double f(graph::node x)
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

	/*%DEBUG%*/
	std::cerr.precision(1);
	uint m = maze.m(), n = maze.n();
	for (uint i = 0u; i < m; i++)
	{
		if (i == 0u)
		{
			for (uint j = 0u; j < n + 1; j++)
				if (j == 0u)
					std::cerr << "    ";
				else
				{
					if (j < 11u)
						std::cerr << "0";
					std::cerr << std::fixed << (double) (j-1) << " ";
				}
			std::cerr << "\n";
		}
		std::cerr << std::fixed << (double) i << " ";
		for (uint j = 0u; j < n; j++)
		{
			if (maze.matrix()[i][j] != maze::OBSTACLE)
			{
				double _f = f(graph::node(i, j));
				if (_f < 10.0)
					std::cerr << "0";
				std::cerr << std::fixed << _f << " ";
			}
			else
			{
				std::cerr << "#### ";
			}
		}
		std::cerr << "\n";
	}
	// return 0;
	/*%DEBUG%*/

	/* Hill Climbing Search Algorithm */
	graph::path solution(source);
	graph::node current = source;
	while (true)
	{
		graph::node next = current;/*%EXECLOG%*/std::cerr << "visit " << current << "\n";
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
double g(uint i, uint j)
{
	return 0.0;
}
double h(uint i, uint j)
{
	return 0.0;
}
