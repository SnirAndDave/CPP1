#include "Parser.h"


int main(int argc, char* argv[])
{
	if (argc != 2)
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

	ofstream fout("Output.txt", ofstream::out);
	Parser parser;
	Puzzle puzzle;
	if (!parser.parse(fin, puzzle, fout))
	{
		fin.close();
		fout.close();
		return 0;
	}

	puzzle.validate(fout);
	fin.close();
	fout.close();
	return 0;
}
