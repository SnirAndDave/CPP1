#include "Parser.h"
#include <iostream>

pair<string, string> parse_arguments(const int argc, char* argv[], int& thread_cnt)
{
	const string rotate = "-rotate";
	if (argc == 3)
	{
		return pair<string, string>(argv[1], argv[2]);
	}
	if (argc != 4)
	{
		cout << "Error: invalid arguments";
		throw exception();
	}
	if (argv[1] == rotate)
	{
		return pair<string, string>(argv[2], argv[3]);
	}
	if (argv[2] == rotate)
	{
		return pair<string, string>(argv[1], argv[3]);
	}
	if (argv[3] == rotate)
	{
		return pair<string, string>(argv[1], argv[2]);
	}
	cout << "Error: invalid arguments";
	throw exception();
}

int main(const int argc, char* argv[])
{
	string fin_path;
	string fout_path;
	int thread_cnt = 5;
	try
	{
		const pair<string, string> pair = parse_arguments(argc, argv, thread_cnt);
		fin_path = pair.first;
		fout_path = pair.second;
	}
	catch (exception)
	{
		return 0;
	}

	const bool rotation_enabled = argc == 4;
	ifstream fin(fin_path, ifstream::in);
	if (!fin.good())
	{
		cout << "error: opening file " + string(fin_path) + " failed";
		return 0;
	}

	ofstream fout(fout_path, ofstream::out);
	Parser parser;
	Puzzle puzzle(fout, rotation_enabled, thread_cnt);
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
