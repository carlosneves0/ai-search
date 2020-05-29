#include "graph.hpp"

graph::node::node():
	_i(0), _j(0)
{}

graph::node::node(uint _i, uint _j):
	_i(_i), _j(_j)
{}


graph::node::node(const maze::position& _p):
	_i(_p.i), _j(_p.j)
{}

graph::node::node(const graph::node& _n):
	_i(_n.i()), _j(_n.j())
{}

unsigned int graph::node::i() const
{
	return this->_i;
}

void graph::node::i(unsigned int _i)
{
	this->_i = _i;
}

unsigned int graph::node::j() const
{
	return this->_j;
}

void graph::node::j(unsigned int _j)
{
	this->_j = _j;
}

bool graph::node::operator==(const graph::node& _n) const
{
	return this->_i == _n.i() && this->_j == _n.j();
}

std::ostream& operator<<(std::ostream& _os, const graph::node& _n)
{
	return _os << "(" << _n.i() << "," << _n.j() << ")";
}
