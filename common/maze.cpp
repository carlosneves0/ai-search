#include "maze.hpp"

const char maze::PATHWAY = '*';
const char maze::OBSTACLE = '-';
const char maze::SOURCE = '#';
const char maze::TARGET = '$';

maze::maze(std::istream& _is)
{
	unsigned int& m = this->m;
	unsigned int& n = this->n;
	char**& matrix = this->matrix;

	_is >> m;
	_is >> n;

	matrix = new char*[m];
	for (unsigned int i = 0u; i < m; i++)
	{
		matrix[i] = new char[n];
		for (unsigned int j = 0u; j < n; j++)
		{
			_is >> matrix[i][j];
			if (matrix[i][j] == maze::SOURCE)
				this->source = {i, j};
			else if (matrix[i][j] == maze::TARGET)
				this->target = {i, j};
		}
	}
}

maze::~maze()
{
	for (unsigned int i = 0u; i < this->m; i++)
		delete [] this->matrix[i];
	delete [] this->matrix;
}


std::ostream& operator<<(std::ostream& _os, const maze& _m)
{
	for (unsigned int i = 0u; i < _m.m; i++)
	{
		for (unsigned int j = 0u; j < _m.n; j++)
			_os << _m.matrix[i][j];
		_os << "\n";
	}
	return _os;
}
