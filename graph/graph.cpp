#include "graph.hpp"

graph::graph(maze& _m):
	_maze(_m)
{
	// Scan maze and extract all nodes (obstacles aren't nodes).
	unsigned int m = _m.m();
	unsigned int n = _m.n();
	char** maze = _m.matrix();
	graph::node x;
	for (unsigned int i = 0u; i < m; i++)
		for (unsigned int j = 0u; j < n; j++)
		{
			if (maze[i][j] == maze::OBSTACLE)
				continue;

			x.i(i), x.j(j);

			if (maze[i][j] == maze::SOURCE)
				this->_source = x;
			else if (maze[i][j] == maze::TARGET)
				this->_target = x;

			this->_nodes.push_back(x);
		}
}

const std::vector<graph::node>& graph::nodes() const
{
	return this->_nodes;
}

graph::node graph::source() const
{
	return this->_source;
}

graph::node graph::target() const
{
	return this->_target;
}

std::vector<graph::node> graph::adjacent_nodes(const graph::node& _n) const
{
	std::vector<graph::node> adjacent_nodes;
	unsigned int i = _n.i(), j = _n.j(), m = this->_maze.m(), n = this->_maze.n();
	maze::position neighbors[] = {{i, j-1}, {i+1, j}, {i, j+1}, {i-1, j}};
	char** maze = this->_maze.matrix();
	for (maze::position& p : neighbors)
	{
		node y(p);
		if (y.i() < m && y.j() < n && maze[y.i()][y.j()] != maze::OBSTACLE)
			adjacent_nodes.push_back(y);
	}
	return adjacent_nodes;
}
