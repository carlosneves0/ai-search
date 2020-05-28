#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>
#include "../maze/maze.hpp"
#include "../graph/graph.hpp"

void print_std_queue(std::priority_queue<graph::path> _q)
{
	std::cerr << "{";
	unsigned int k = _q.size() - 1;
	while(!_q.empty())
	{
		std::cerr << _q.top() << (k-- > 0 ? ", " : "");
		_q.pop();
	}
	std::cerr << "}\n";
}

maze* maze_instance = nullptr;
double h(unsigned int i, unsigned int j)
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
	typedef unsigned int uint;
	std::cout.precision(1);
	uint m = maze.m(), n = maze.n();
	for (uint i = 0u; i < m; i++)
	{
		if (i == 0u)
		{
			for (uint j = 0u; j < n + 1; j++)
				if (j == 0u)
					std::cout << "    ";
				else
				{
					if (j < 11u)
						std::cout << "0";
					std::cout << std::fixed << (double) (j-1) << " ";
				}
			std::cout << "\n";
		}
		std::cout << std::fixed << (double) i << " ";
		for (uint j = 0u; j < n; j++)
		{
			if (maze.matrix()[i][j] != maze::OBSTACLE)
			{
				double _h = h(i, j);
				if (_h < 10)
					std::cout << "0";
				std::cout << std::fixed << _h << " ";
			}
			else
			{
				std::cout << "#### ";
			}
		}
		std::cout << "\n";
	}
	// return 0;
	//---DEBUG

	graph graph(maze);
	graph::node source = graph.source();
	graph::node target = graph.target();

	/* Greedy Best First Search Algorithm */
	std::priority_queue<graph::path> L;
	graph::path initial_path(source); L.push(initial_path);
	bool visited[maze.m()][maze.n()]; std::fill(*visited, *visited + maze.m()*maze.n(), false);

	while (!L.empty())
	{
		// print_std_queue(L);

		graph::path p = L.top(); L.pop();
		graph::node x = p.last_node(); /*EXECLOG/ std::cerr << "goto " << x.i() << "," << x.j() << "\n"; /*/

		if (!visited[x.i()][x.j()])
		{
			std::cerr << "visit " << x << "\n";
			visited[x.i()][x.j()] = true;

			if (x == target)
			{
				std::cout << p << "\n";
				return 0;
			}

			for (graph::node& y : graph.adjacent_nodes(x))
				if (!visited[y.i()][y.j()])
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
