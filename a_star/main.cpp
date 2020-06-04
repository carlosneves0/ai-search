#define __A_STAR__
#include <iostream>
#include <cmath>
#include <queue>
#include "../maze/maze.hpp"
#include "../graph/graph.hpp"
typedef unsigned int uint;

/* Global maze instance */
maze* maze_instance = nullptr;

/** Cost matrix. Used by g(x)
 * For each position (i,j) => the length of the shortest path that begins at
 * source and ends in (i,j).
 * The functions are defined below main().
 */
uint** cost_matrix = nullptr;
void init_cost_matrix();
void free_cost_matrix();
void add_path_to_cost_matrix(const graph::node& _n, const graph::path& _p);

/** Cost function g(x)
 * g(x) is the linear distance from source to x.
 */
double g(graph::node& x)
{
	if (!cost_matrix)
		init_cost_matrix();
	uint i = x.i(), j = x.j();
	return (double) cost_matrix[i][j];
}

/** Heuristic function h(x)
 * h(x) is the linear distance from x to target.
 */
double h(graph::node& x)
{
	static maze::position target = maze_instance->target();
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

	/* A* Search Algorithm */
	std::priority_queue<graph::path> L;
	graph::path initial_path(source); L.push(initial_path);

	while (!L.empty())
	{
		graph::path p = L.top(); L.pop();
		graph::node x = p.last_node();

		if (!graph.was_visited(x))
		{
			graph.visit(x);
			add_path_to_cost_matrix(x, p);

			if (x == target)
			{
				std::cout << p << "\n";
				free_cost_matrix();
				return 0;
			}

			for (graph::node& y : graph.adjacent_nodes(x))
				if (!graph.was_visited(y))
				{
					graph::path new_path(p, y);
					add_path_to_cost_matrix(y, new_path);
					L.push(new_path);
				}
		}
	}

	std::cout << "No solutions were found for this maze.\n";
	free_cost_matrix();
	return 1;
}

void init_cost_matrix()
{
	uint m = maze_instance->m(), n = maze_instance->n();
	cost_matrix = new uint*[m];
	for (uint i = 0u; i < m; i++)
	{
		cost_matrix[i] = new uint[n];
		for (uint j = 0u; j < n; j++)
			cost_matrix[i][j] = -1u;
	}
}
void free_cost_matrix()
{
	for (uint i = 0u, m = maze_instance->m(); i < m; i++)
		delete [] cost_matrix[i];
	delete [] cost_matrix;
}

void add_path_to_cost_matrix(const graph::node& _n, const graph::path& _p)
{
	if (!cost_matrix)
		init_cost_matrix();
	uint i = _n.i(), j = _n.j();
	if (cost_matrix[i][j] > _p.length())
		cost_matrix[i][j] = _p.length();
}
