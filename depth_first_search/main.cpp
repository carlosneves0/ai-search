#define __DEPTH_FIRST_SEARCH__
#include <iostream>
#include <stack>
#include <algorithm>
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

	/* Depth First Search Algorithm */
	std::stack<graph::path> L;
	graph::path initial_path(source); L.push(initial_path);
	bool visited[maze.m()][maze.n()]; std::fill(*visited, *visited + maze.m()*maze.n(), false);

	while (!L.empty())
	{
		graph::path p = L.top(); L.pop();
		graph::node x = p.last_node();

		if (x == target)
		{
			std::cout << p << "\n";
			return 0;
		}

		if (!visited[x.i()][x.j()])
		{
			visited[x.i()][x.j()] = true;
			for (graph::node& y : graph.adjacent_nodes(x))
				if (!visited[y.i()][y.j()])
				{
					graph::path new_path(p); new_path.add_node(y);
					L.push(new_path);
				}
		}
	}

	std::cout << "No solutions were found for this maze.\n";
	return 0;
}

// These two must be here to be able to link.
// Cost function g.
double g(graph::node& x)
{
	return 0.0;
}
// Heuristic function h.
double h(graph::node& x)
{
	return 0.0;
}
