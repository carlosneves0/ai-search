#define __BREADTH_FIRST_SEARCH__
#include <iostream>
#include <list>
#include "../maze/maze.hpp"
#include "../graph/graph.hpp"
typedef unsigned int uint;

int main()
{
	/* Read and convert stdin into meaningful data structures. */
	maze maze(std::cin);
	graph graph(maze);
	graph::node source = graph.source();
	graph::node target = graph.target();

	/* Breadth First Search Algorithm */
	std::list<graph::path> L;
	graph::path initial_path(source); L.push_back(initial_path);

	while (!L.empty())
	{
		graph::path p = L.front(); L.pop_front();
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
					L.push_back(new_path);
				}
		}
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
