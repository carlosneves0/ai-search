#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <set>
#include "maze.hpp"

class graph {
public:
	class node {
	public:
		node(unsigned int _i, unsigned int _j, bool _visited = false, node* _trace = nullptr);
		unsigned int i() const;
		unsigned int j() const;
		bool visited() const;
		void visit();
		node* trace() const;
		void trace(node* _n);
		void reset();
		bool operator==(const node& _rhs);
		friend std::ostream& operator<<(std::ostream& _os, const node& _n);
	private:
		unsigned int _i, _j;
		bool _visited;
		node* _trace;
	};
	graph(maze& _maze);
	~graph();
	node* find(maze::position& _p);
	std::set<node*> adjacent_nodes(node& _n);
private:
	unsigned int m, n;
	node*** nodes;
};

#endif
