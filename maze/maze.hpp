#ifndef __MAZE_HPP__
#define __MAZE_HPP__
#include <iostream>
typedef unsigned int uint;

class maze
{
public:
	struct position { uint i, j; };

public:
	static const char PATHWAY, OBSTACLE, SOURCE, TARGET;

public:
	maze(std::istream& _is);
	~maze();
	uint m() const;
	uint n() const;
	char** matrix() const;
	maze::position source() const;
	maze::position target() const;
	friend std::ostream& operator<<(std::ostream& _os, const maze& _m);

private:
	uint _m, _n;
	char** _matrix;
	maze::position _source;
	maze::position _target;
};

#endif
