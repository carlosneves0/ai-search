#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <vector>
#include "../maze/maze.hpp"

class graph {
public:
	class node {
	public:
		node();
		node(const maze::position& _p);
		unsigned int i() const;
		void i(unsigned int _i);
		unsigned int j() const;
		void j(unsigned int _j);
		bool operator==(const graph::node& _n) const;
		friend std::ostream& operator<<(std::ostream& _os, const graph::node& _n);
	private:
		unsigned int _i, _j;
	};

public:
	class path {
	public:
		path(graph::node _initial_node);
		path(const graph::path& _p);
		const std::vector<graph::node>& nodes() const;
		graph::node& last_node();
		void add_node(graph::node& _n);
		friend std::ostream& operator<<(std::ostream& _os, const graph::path& _p);
	private:
		std::vector<graph::node> _nodes;
	};

public:
	graph(maze& _m);
	const std::vector<graph::node>& nodes() const;
	graph::node source() const;
	graph::node target() const;
	std::vector<graph::node> adjacent_nodes(const graph::node& _n) const;

private:
	maze& _maze;
	std::vector<graph::node> _nodes;
	graph::node _source;
	graph::node _target;
};

#endif
