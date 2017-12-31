#include "Parser.h"
#include <iostream>
#include <iterator>

bool cmdOptionExists(vector<char*> vec, const std::string& option)
{
	return std::find(vec.begin(), vec.end(), option) != vec.end();
}

int cmdOptionIndex(vector<char*> vec, const std::string& option)
{
	auto it = std::find(vec.begin(), vec.end(), option);
	if (it == vec.end())
	{
		return -1;
	}
	auto index = std::distance(vec.begin(), it);
	return index;
}

char* getCmdOption(vector<char*> vec, const std::string& option)
{
	return vec[cmdOptionIndex(vec, option)];
}

pair<string, string> parse_arguments(const int argc, char* argv[], int& thread_cnt, bool& is_rotation_enabled)
{
	const string rotate = "-rotate";
	const string threads = "-threads";
	vector<char*> argv_vec(argv, argv+argc);
	if (argc == 3)
	{
		return pair<string, string>(argv_vec[1], argv_vec[2]);
	}
	if(cmdOptionExists(argv_vec, rotate))
	{
		is_rotation_enabled = true;
		argv_vec.erase(std::find(argv_vec.begin(), argv_vec.end(), rotate));
	}
	if(cmdOptionExists(argv_vec, threads))
	{
		int index = cmdOptionIndex(argv_vec, threads);
		if(index + 1 >= int(argv_vec.size()))
		{
			// -threads is the last argument
			cout << "usage: -threads THREAD_COUNT" << endl;
			throw invalid_argument(threads);
		}
		try
		{
		thread_cnt = stoi(argv_vec[index + 1]);
		}
		catch(exception)
		{
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
	try
	{
		const pair<string, string> pair = parse_arguments(argc, argv, thread_cnt, rotation_enabled);
		fin_path = pair.first;
		fout_path = pair.second;
	}
	catch (exception ex)
	{
		cout << "failed to parse arguments with exception: "<< endl << ex.what() << endl;
		return 0;
	}
	cout << "solving puzzle from file: " << fin_path << " into file: " << fout_path << " with " << thread_cnt << " threads and rotation = " << rotation_enabled;
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
