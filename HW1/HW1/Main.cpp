#include "Parser.h"
#include <iostream>
#include <iterator>
#include <cassert>

/**
 * Checks if given flag exists in cmd line
 */
bool cmdOptionExists(vector<char*> vec, const std::string& option)
{
	return std::find(vec.begin(), vec.end(), option) != vec.end();
}

/**
 * Returns index of given flag in cmd line
 */
int cmdOptionIndex(vector<char*> vec, const std::string& option)
{
	const auto it = std::find(vec.begin(), vec.end(), option);
	if (it == vec.end())
	{
		return -1;
	}
	const auto index = std::distance(vec.begin(), it);
	return index;
}

char* getCmdOption(vector<char*> vec, const std::string& option)
{
	return vec[cmdOptionIndex(vec, option)];
}

/**
 * Parse arguments from command line. Handles the flags -rotate and -threads
 */
pair<string, string> parse_arguments(const int argc, char* argv[], int& thread_cnt, bool& is_rotation_enabled)
{
	const string rotate = "-rotate";
	const string threads = "-threads";
	vector<char*> argv_vec(argv, argv + argc);
	if (argc == 3)
	{
		return pair<string, string>(argv_vec[1], argv_vec[2]);
	}
	if (cmdOptionExists(argv_vec, rotate))
	{
		is_rotation_enabled = true;
		argv_vec.erase(std::find(argv_vec.begin(), argv_vec.end(), rotate));
	}
	if (cmdOptionExists(argv_vec, threads))
	{
		const int index = cmdOptionIndex(argv_vec, threads);
		if (index + 1 >= int(argv_vec.size()))
		{
			// -threads is the last argument
			cout << "usage: -threads THREAD_COUNT" << endl;

			throw invalid_argument(threads);
		}
		try
		{
			thread_cnt = stoi(argv_vec[index + 1]);
		}
		catch (exception ex)
		{
			cout << "usage: -threads THREAD_COUNT" << endl;
			throw invalid_argument(threads);
		}
		argv_vec.erase(argv_vec.begin() + index + 1);
		argv_vec.erase(argv_vec.begin() + index);
	}
	return pair<string, string>(argv_vec[1], argv_vec[2]);
}

int main(const int argc, char* argv[])
{
	string fin_path;
	string fout_path;

	int thread_cnt = 4;
	bool rotation_enabled = false;

	ParserErrorCode ec = ParserErrorCode::no_errors;

	//1. Try to parse cmd line first
	try
	{
		const pair<string, string> pair = parse_arguments(argc, argv, thread_cnt, rotation_enabled);
		fin_path = pair.first;
		fout_path = pair.second;
	}
	catch (exception ex)
	{
		ec = ParserErrorCode::parse_arguments_error;
		cout << make_error_code(ec).message() << endl << "with exception: " << ex.what() << endl;
		return 0;
	}
	cout << "solving puzzle from file: " << fin_path << " into file: " << fout_path << " with " << thread_cnt <<
		" threads and rotation = " << rotation_enabled << endl;

	ifstream fin(fin_path, ifstream::in);
	if (!fin.good())
	{
		ec = ParserErrorCode::open_file_error;
		cout << make_error_code(ec).message() << endl << "opening file " + string(fin_path) + " failed";
		return 0;
	}

	ofstream fout(fout_path, ofstream::out);
	if (!fout.good())
	{
		ec = ParserErrorCode::open_file_error;
		cout << make_error_code(ec).message() << endl << "opening or creating file " + string(fout_path) + " failed";
		return 0;
	}
	const Parser parser;
	Puzzle puzzle(fout, rotation_enabled, thread_cnt);

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
