#include <iostream>

using namespace std;

typedef unsigned int uint;
typedef unsigned char uchar;

int main()
{
	/* stdin */
	uint nlines, ncolumns;
	cin >> nlines;
	cin >> ncolumns;

	uchar maze[nlines][ncolumns];
	for (uint i = 0u; i < nlines; i++)
		for (uint j = 0u; j < ncolumns; j++)
			cin >> maze[i][j];

	/* search algorithm */
	// TODO: log to stderr

	/* stdout */
	for (uint i = 0u; i < nlines; i++)
	{
		for (uint j = 0u; j < ncolumns; j++)
			cout << maze[i][j];
		cout << "\n";
	}

	return 0;
}
