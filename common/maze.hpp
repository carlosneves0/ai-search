#ifndef __MAZE_HPP__
#define __MAZE_HPP__

#include <iostream>

class maze
{
public:
	static const char PATHWAY, OBSTACLE, SOURCE, TARGET;
	struct position { unsigned int i, j; };
	maze(std::istream& _is);
	~maze();
	friend std::ostream& operator<<(std::ostream& _os, const maze& _m);
	unsigned int m, n;
	char** matrix;
	position source;
	position target;
};

#endif
