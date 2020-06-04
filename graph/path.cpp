#include "graph.hpp"

graph::path::path(graph::node& _initial_node)
{
	this->_nodes.push_back(_initial_node);
}

graph::path::path(const graph::path& _p)
{
	for (graph::node x : _p.nodes())
		this->_nodes.push_back(x);
}

graph::path::path(const graph::path& _p, graph::node& _new_node)
{
	for (graph::node x : _p.nodes())
		this->_nodes.push_back(x);
	this->_nodes.push_back(_new_node);
}

const std::vector<graph::node>& graph::path::nodes() const
{
	return this->_nodes;
}

graph::node graph::path::last_node() const
{
	return this->_nodes.back();
}

void graph::path::add_node(graph::node& _n)
{
	this->_nodes.push_back(_n);
}

uint graph::path::length() const
{
	return this->_nodes.size() - 1;
}

bool operator<(const graph::path& _r, const graph::path& _l)
{
	graph::node l = _l.last_node();
	graph::node r = _r.last_node();
	double fl = g(l) + h(l);
	double fr = g(r) + h(r);
	return fl < fr;
}

std::ostream& operator<<(std::ostream& _os, const graph::path& _p)
{
	const std::vector<graph::node>& path = _p.nodes();
	_os << "[";
	uint path_length = path.size();
	for (uint i = 0u; i < path_length; i++)
		_os << path[i] << (i < path_length - 1u ? ", " : "");

	/*%EXECLOG%*/
	std::cerr << "succeed [";
	for (uint i = 0u; i < path_length; i++)
	{
		const graph::node& n = path[i];
		std::cerr << "[" << n.i() << "," << n.j() << "]";
		if (i < path_length - 1u) {
			std::cerr << ",";
		}
	}
	std::cerr << "]\n";
	/*%EXECLOG%*/

	return _os << "]";
}
