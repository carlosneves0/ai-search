#ifndef __MAZE_HPP__
#define __MAZE_HPP__

#include <iostream>

class maze
{
public:
	struct position { unsigned int i, j; };

public:
	static const char PATHWAY, OBSTACLE, SOURCE, TARGET;

public:
	maze(std::istream& _is);
	~maze();
	unsigned int m() const;
	unsigned int n() const;
	char** matrix() const;
	maze::position source() const;
	maze::position target() const;
	friend std::ostream& operator<<(std::ostream& _os, const maze& _m);

private:
	unsigned int _m, _n;
	char** _matrix;
	maze::position _source;
	maze::position _target;
};

#endif
