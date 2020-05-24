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
