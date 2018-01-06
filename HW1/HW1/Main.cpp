#include "Parser.h"
#include <iostream>
#include <iterator>
#include <cassert>
#include <algorithm>

int main(const int argc, char* argv[])
{
	ParserErrorCode ec = ParserErrorCode::no_errors;
	
	//1. Try to parse cmd line first
	Parser parser;
	try
	{
		parser.parse_arguments(argc, argv);
	}
	catch (exception ex)
	{
		ec = ParserErrorCode::parse_arguments_error;
		cout << make_error_code(ec).message() << endl << "with exception: " << ex.what() << endl;
		return 0;
	}
	cout << "solving puzzle from file: " << parser._fin_path << " into file: " << parser._fout_path << " with " << parser._thread_cnt <<
		" threads and rotation = " << parser._rotation_enabled << endl;

	ifstream fin(parser._fin_path, ifstream::in);
	if (!fin.good())
	{
		ec = ParserErrorCode::open_file_error;
		cout << make_error_code(ec).message() << endl << "opening file " + string(parser._fin_path) + " failed";
		return 0;
	}

	ofstream fout(parser._fout_path, ofstream::out);
	if (!fout.good())
	{
		ec = ParserErrorCode::open_file_error;
		cout << make_error_code(ec).message() << endl << "opening or creating file " + string(parser._fout_path) + " failed";
		return 0;
	}
	Puzzle puzzle(fout, parser._rotation_enabled, parser._thread_cnt);

	//2. Try to parse input files
	if (!parser.parse(fin, puzzle, fout, &ec))
	{
		fin.close();
		fout.close();
		return 0;
	}
	assert(ec == ParserErrorCode::no_errors);
	//3. Solve puzzle
	puzzle.solve();
	fin.close();
	fout.close();
	return 0;
}
