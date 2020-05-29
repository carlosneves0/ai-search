#define __BEST_FIRST_SEARCH__
#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
#include "../maze/maze.hpp"
#include "../graph/graph.hpp"
typedef unsigned int uint;

/* Global maze instance */
maze* maze_instance = nullptr;

// Cost function g.
double g(uint i, uint j)
{
	return 0.0;
}

/* Greedy Best-First heuristic function h */
double h(uint i, uint j)
{
	static maze::position target = (*maze_instance).target();
	uint ti = target.i, tj = target.j;
	return std::sqrt(std::pow((double) ti - i, 2.0) + std::pow((double) tj - j, 2.0));
}

// Which nodes were already visited.
bool** _visited = nullptr;
void init_visited();
bool visited(graph::node& x);
void visit(graph::node& x);

int main()
{
	/* Read and convert stdin into meaningful data structures. */
	maze maze(std::cin); maze_instance = &maze;

	graph graph(maze);

	graph::node source = graph.source(), target = graph.target();

	init_visited();

	/* Greedy Best First Search Algorithm */
	std::priority_queue<graph::path> L;
	graph::path initial_path(source); L.push(initial_path);

	while (!L.empty())
	{
		graph::path p = L.top(); L.pop();
		graph::node x = p.last_node();

		if (!visited(x))
		{
			visit(x);

			if (x == target)
			{
				std::cout << p << "\n";
				return 0;
			}

			for (graph::node& y : graph.adjacent_nodes(x))
				if (!visited(y))
				{
					graph::path new_path(p); new_path.add_node(y);
					L.push(new_path);
				}
		}
	}

	std::cout << "No solutions were found for this maze.\n";
	return 0;
}

void init_visited()
{
	maze& maze = *maze_instance;
	_visited = new bool*[maze.m()];
	for (uint i = 0u; i < maze.m(); i++)
	{
		_visited[i] = new bool[maze.n()];
		for (uint j = 0u; j < maze.n(); j++)
			_visited[i][j] = false;
	}
}

bool visited(graph::node& x)
{
	return _visited[x.i()][x.j()];
}

void visit(graph::node& x)
{
	_visited[x.i()][x.j()] = true;
}
