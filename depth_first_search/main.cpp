#include <iostream>
#include <stack>
#include "../common/maze.hpp"
#include "../common/graph.hpp"

int main()
{
	/* stdin */
	maze maze(std::cin);
	graph graph(maze);
	graph::node* source = graph.find(maze.source);
	graph::node& target = *graph.find(maze.target);

	/* search algorithm */
	// TODO: send execlog to stderr

	// Depart from the source node.
	std::stack<graph::node*> stack;
	stack.push(source);

	while (!stack.empty())
	{
		graph::node& x = *stack.top(); stack.pop();
		// std::cerr << "visit " << x << "\n"; // %EXECLOG%

		if (x == target)
		{
			std::stack<graph::node*> path;
			graph::node* y = &x;
			do
			{
				path.push(y);
				y = y->trace();
			}
			while (y);

			std::cout << "[";
			bool first = true;
			while (!path.empty())
			{
				y = path.top(); path.pop();
				std::cout << (first ? "" : ", ") << *y;
				if (first)
					first = false;
			}
			std::cout << "]\n";
			break;
		}

		if (!x.visited())
		{
			x.visit();
			for (graph::node* y_addr : graph.adjacent_nodes(x))
			{
				graph::node& y = *y_addr;
				if (!y.visited())
				{
					y.trace(&x);
					// std::cerr << "y.trace " << *(y.trace()) << "\n"; // %EXECLOG%
					stack.push(y_addr);
					// std::cerr << "push " << y << "\n"; // %EXECLOG%
				}
			}
		}
	}

	return 0;
}







// class node_t
// {
// private:
// 	uint _i, _j;
// 	node_t* _trace;
// public:
// 	node_t(uint _i = 0u, uint _j = 0u): _i(_i), _j(_j), _trace(nullptr) {};
// 	node_t(const node_t& _x): _i(_x.i()), _j(_x.j()) {
// 		node_t* xtrace = _x.trace();
// 		if (xtrace)
// 			this->_trace = new node_t(xtrace->i(), xtrace->j());
// 		else
// 			this->_trace = nullptr;
// 	};
// 	~node_t()
// 	{
// 		if (this->_trace)
// 			delete this->_trace;
// 	};
// 	uint i() const { return this->_i; }
// 	uint j() const { return this->_j; }
// 	node_t* trace() const { return this->_trace; }
// 	node_t& i(uint _i) { this->_i = _i; return *this; }
// 	node_t& j(uint _j) { this->_j = _j; return *this; }
// 	node_t& trace(const node_t& _trace)
// 	{
// 		if (this->_trace)
// 			delete this->_trace;
// 		this->_trace = new node_t(_trace);
// 		return *this;
// 	}
// 	bool operator==(const node_t& _rhs) { return this->_i == _rhs.i() && this->_j == _rhs.j(); }
// 	friend std::ostream& operator<<(std::ostream& _os, const node_t& _x) { return _os << "(" << _x.i() << ", " << _x.j() << ")"; };
// };
//
// const char MAZE_PATHWAY = '*';
// const char MAZE_OBSTACLE = '-';
// const char MAZE_SOURCE = '#';
// const char MAZE_TARGET = '$';
