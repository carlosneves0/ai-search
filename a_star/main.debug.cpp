#define __A_STAR__
#include <iostream>
#include <cmath>
#include <queue>
#include "../maze/maze.hpp"
#include "../graph/graph.hpp"
typedef unsigned int uint;

void print_std_queue(std::priority_queue<graph::path> _q)
{
	std::cerr << "{";
	uint k = _q.size() - 1;
	while(!_q.empty())
	{
		std::cerr << _q.top() << (k-- > 0 ? ", " : "");
		_q.pop();
	}
	std::cerr << "}\n";
}

maze* maze_instance = nullptr;
// Which nodes were already visited.
bool** _visited = nullptr;
void init_visited();
bool visited(graph::node& x);
void visit(graph::node& x);

double g(uint i, uint j)
{
	static maze::position source = (*maze_instance).source();
	uint ti = source.i, tj = source.j;
	return std::sqrt(std::pow((double) ti - i, 2.0) + std::pow((double) tj - j, 2.0));
}

double h(uint i, uint j)
{
	static maze::position target = (*maze_instance).target();
	uint ti = target.i, tj = target.j;
	return std::sqrt(std::pow((double) ti - i, 2.0) + std::pow((double) tj - j, 2.0));
}

/**
 * TODO: send execlog to stderr.
 */
int main()
{
	/* Read and convert stdin into meaningful data structures. */
	maze maze(std::cin); maze_instance = &maze;

	//---DEBUG
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
				double _f = g(i, j) + h(i, j);
				if (_f < 10)
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
	//---DEBUG

	graph graph(maze);
	graph::node source = graph.source();
	graph::node target = graph.target();

	/* Greedy Best First Search Algorithm */
	std::priority_queue<graph::path> L;
	graph::path initial_path(source); L.push(initial_path);
	init_visited();

	while (!L.empty())
	{
		// print_std_queue(L);

		graph::path p = L.top(); L.pop();
		graph::node x = p.last_node(); /*EXECLOG/ std::cerr << "goto " << x.i() << "," << x.j() << "\n"; /*/

		if (!visited(x))
		{
			std::cerr << "visit " << x << "\n";
			visit(x);

			if (x == target)
			{
				std::cout << p << "\n";
				return 0;
			}

			for (graph::node& y : graph.adjacent_nodes(x))
				if (!visited(y))
				{
					std::cerr << "discover " << y << "\n";
					graph::path new_path(p); new_path.add_node(y);
					L.push(new_path);
				}
		}
	}

	std::cout << "No solutions were found for this maze.\n";
	return 0;
}

// TODO: put these visited things inside the graph class.
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
