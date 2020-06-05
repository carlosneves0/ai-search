#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__
#include <vector>
#include "../maze/maze.hpp"
typedef unsigned int uint;

class graph {
public:
	class node {
	public:
		node();
		node(uint _i, uint _j);
		node(const maze::position& _p);
		node(const graph::node& _n);
		uint i() const;
		void i(uint _i);
		uint j() const;
		void j(uint _j);
		bool operator==(const graph::node& _n) const;
		friend std::ostream& operator<<(std::ostream& _os, const graph::node& _n);
	private:
		uint _i, _j;
	};

public:
	class path {
	public:
		path(graph::node& _initial_node);
		path(const graph::path& _p);
		path(const graph::path& _p, graph::node& _new_node);
		const std::vector<graph::node>& nodes() const;
		graph::node last_node() const;
		void add_node(graph::node& _n);
		uint length() const;
#if defined(__A_STAR__) || defined(__BEST_FIRST_SEARCH__)
		friend bool operator<(const graph::path& _r, const graph::path& _l);
#endif
		friend std::ostream& operator<<(std::ostream& _os, const graph::path& _p);
	private:
		std::vector<graph::node> _nodes;
	};

public:
	graph(maze& _m);
	~graph();
	bool was_visited(graph::node& _n) const;
	void visit(graph::node& _n);
	const std::vector<graph::node>& nodes() const;
	graph::node source() const;
	graph::node target() const;
	std::vector<graph::node> adjacent_nodes(const graph::node& _n) const;

private:
	maze& _maze;
	bool** visited;
	std::vector<graph::node> _nodes;
	graph::node _source;
	graph::node _target;
};

// Global cost and heuristic functions g and h. Both defined by the user.
double g(graph::node& x);
double h(graph::node& x);

#endif
