#include "Parser.h"
#include <iostream>


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Error: 1 argmunt must be provided";
		return 0;
	}

	ifstream fin(argv[1], ifstream::in);
	if (!fin.good())
	{
		cout << "error: opening file " + string(argv[1]) + " failed";
		return false;
	}

	ofstream fout(argv[2], ofstream::out);
	Parser parser;
	Puzzle puzzle(fout);
	if (!parser.parse(fin, puzzle, fout))
	{
		fin.close();
		fout.close();
		return 0;
	}

	puzzle.solve();
	fin.close();
	fout.close();
	return 0;
}
