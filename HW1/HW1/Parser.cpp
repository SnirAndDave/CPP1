#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Parser.h"
#include <iterator>
#include <ctype.h>

using namespace std;


void Parser::get_missing_elements(const Puzzle& puzzle, vector<int>& missing_elements)
{
	int rel_size = puzzle.size + 1;
	bool* ids = new bool[rel_size];
	fill_n(ids, rel_size, false); //initialize with false

	for (auto it = puzzle.elements.begin(); it != puzzle.elements.end(); ++it)
	{
		// assume that each id has value < puzzle.size (it is checked)
		ids[it->id] = true;
	}
	for (auto i = 1; i < rel_size; i++)
	{
		if (!ids[i])
		{
			missing_elements.push_back(i);
		}
	}
}

bool Parser::check_if_valid_and_report_error(const Puzzle& puzzle, ofstream& fout, vector<int>& missing_elements,
                                             vector<int>& wrong_ids, vector<string>& bad_format_lines,
                                             vector<string>& bad_format_ids)
{
	bool is_valid = true;
	get_missing_elements(puzzle, missing_elements);

	if (!missing_elements.empty())
	{
		ostringstream oss;
		oss << "Missing puzzle element(s) with the following IDs: ";
		is_valid = false;

		get_ids_with_comma_delimiter(missing_elements, oss);
		fout << oss.str() << endl;
	}
	if (!wrong_ids.empty())
	{
		std::ostringstream oss;
		oss << "Puzzle of size " << puzzle.size << " cannot have the following IDs: ";
		is_valid = false;

		get_ids_with_comma_delimiter(wrong_ids, oss);
		fout << oss.str() << endl;
	}
	if (!bad_format_lines.empty())
	{
		is_valid = false;
		for (auto const& line : bad_format_lines)
		{
			vector<string> delimited = split(line, ' ');
			int id = stoi(delimited[0]);
			fout << "Puzzle ID " << id << " has wrong data: " << line << endl;
		}
	}
	if (!bad_format_ids.empty())
	{
		is_valid = false;
		ostringstream oss;
		oss << "The following element(s) doesn't have a valid ID: ";

		string last_id = bad_format_ids.back();
		bad_format_ids.pop_back();
		for (string id : bad_format_ids)
		{
			oss << id << ", ";
		}
		oss << last_id;
		fout << oss.str() << endl;
	}
	return is_valid;
}

void Parser::get_ids_with_comma_delimiter(vector<int>& elements, ostringstream& oss)
{
	copy(elements.begin(), elements.end() - 1,
	     ostream_iterator<int>(oss, ", "));

	// Now add the last element with no delimiter
	oss << elements.back();
}

bool Parser::parse(ifstream& fin, Puzzle& puzzle, ofstream& fout)
{
	string line;
	vector<int> missing_elements;
	vector<int> wrong_ids;
	vector<string> bad_format_lines;
	vector<string> bad_format_ids;

	try
	{
		getline(fin, line);
		clean_spaces(line);
		puzzle.size = process_first_line(line);
		while (getline(fin, line))
		{
			this->processLine(line, wrong_ids, bad_format_lines, bad_format_ids, puzzle.size, puzzle.elements);
		}

		return check_if_valid_and_report_error(puzzle, fout, missing_elements, wrong_ids, bad_format_lines, bad_format_ids);
	}
	catch (exception ex)
	{
		//	fout << "Failed to parse input file - with exception: " << ex.what() << endl;
		fout << "" << ex.what() << endl;
		//cout << ex.what() << endl;
		return false;
	}
}

int Parser::process_first_line(const string& line)
{
	vector<string> delimited = split(line, '=');
	string num = delimited[1];
	if (!is_digits(num))
	{
		throw exception("invalid number of elements");
	}
	return stoi(num);
}

int Parser::parse_edge(string edge)
{
	if (!is_digits_with_minus(edge))
	{
		throw exception("edge is not a number");
	}
	int parsed = stoi(edge);
	if (parsed < -1 || parsed > 1)
	{
		throw exception("edge is not valid number");
	}
	return parsed;
}

bool Parser::is_digits(const std::string& str)
{
	return std::all_of(str.begin(), str.end(), ::isdigit);
}

bool Parser::is_digits_with_minus(const std::string& str)
{
	if (str[0] == '-')
	{
		string str2 = str.substr(1, str.size());
		return std::all_of(str2.begin(), str2.end(), ::isdigit);
	}
	return std::all_of(str.begin(), str.end(), ::isdigit);
}

void Parser::processLine(const string& line, vector<int>& wrong_ids, vector<string>& bad_format_lines,
                         vector<string>& bad_format_ids,
                         int elements_count,
                         vector<Element>& elements)
{
	vector<string> delimited = split(line, ' ');


	if (!is_digits(delimited[0]))
	{
		bad_format_ids.push_back(delimited[0]);
		return;
	}

	int id = stoi(delimited[0]);

	if (id > elements_count || id <= 0)
	{
		wrong_ids.push_back(id);
		return;
	}

	try
	{
		int left = parse_edge(delimited[1]);
		int top = parse_edge(delimited[2]);
		int right = parse_edge(delimited[3]);
		int bottom = parse_edge(delimited[4]);

		Element el(id, left, top, right, bottom);
		elements.push_back(el);
	}
	catch (exception ex)
	{
		bad_format_lines.push_back(line);
		Element el(id, 0, 0, 0, 0);
		elements.push_back(el);
	}
}

void Parser::clean_spaces(string& str)
{
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

//splits string s to a vector
vector<string> Parser::split(const string& s, char delim)
{
	vector<string> elems;
	stringstream str_st(s);
	string item;

	while (getline(str_st, item, delim)) //we could ommit the '' notion from here.
	{
		elems.push_back(item); //push_back is a function of vector class, it inserted to the back of the vector.
	}

	return elems;
}
