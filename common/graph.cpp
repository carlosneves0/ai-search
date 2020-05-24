#include "graph.hpp"

/**
 * node
 */
graph::node::node(unsigned int _i, unsigned int _j, bool _visited, node* _trace):
	_i(_i), _j(_j), _visited(_visited), _trace(_trace)
{}

unsigned int graph::node::i() const
{
	return this->_i;
}

unsigned int graph::node::j() const
{
	return this->_j;
}

bool graph::node::visited() const
{
	return this->_visited;
}

void graph::node::visit()
{
	this->_visited = true;
}

graph::node* graph::node::trace() const
{
	return this->_trace;
}

void graph::node::trace(node* _n)
{
	this->_trace = _n;
}

void graph::node::reset()
{
	this->_visited = false;
	this->_trace = nullptr;
}

bool graph::node::operator==(const graph::node& _rhs)
{
	return this->_i == _rhs.i() && this->_j == _rhs.j();
}

std::ostream& operator<<(std::ostream& _os, const graph::node& _n)
{
	return _os << "(" << _n.i() << "," << _n.j() << ")";
}

/**
 * graph
 */
graph::graph(maze& _maze)
{
	this->m = _maze.m;
	this->n = _maze.n;
	this->nodes = new graph::node**[_maze.m];
	for (unsigned int i = 0u; i < _maze.m; i++)
	{
		this->nodes[i] = new graph::node*[_maze.n];
		for (unsigned int j = 0u; j < _maze.n; j++)
			if (_maze.matrix[i][j] != maze::OBSTACLE)
				this->nodes[i][j] = new graph::node(i, j);
			else
				this->nodes[i][j] = nullptr;
	}
}

graph::~graph()
{
	for (unsigned int i = 0u; i < this->m; i++)
	{
		for (unsigned int j = 0u; j < this->n; j++)
			if (this->nodes[i][j])
				delete this->nodes[i][j];
		delete[] this->nodes[i];
	}
	delete[] this->nodes;
}

// NOTE: this function might return `nullptr`.
graph::node* graph::find(maze::position& _p)
{
	return this->nodes[_p.i][_p.j];
}

std::set<graph::node*> graph::adjacent_nodes(graph::node& _n)
{
	std::set<graph::node*> adjacent_nodes;

	unsigned int i = _n.i(), j = _n.j();

	maze::position maze_neighbors[] = {{i-1u, j}, {i+1u, j}, {i, j-1u}, {i, j+1u}};
	for (maze::position& k : maze_neighbors)
		if (k.i < this->m && k.j < this->n)
			if (this->nodes[k.i][k.j])
				adjacent_nodes.insert(this->nodes[k.i][k.j]);

	return adjacent_nodes;
}
