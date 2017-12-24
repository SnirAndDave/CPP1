#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Parser.h"
#include <iterator>
#include <cctype>

using namespace std;


bool Parser::get_missing_elements(const Puzzle& puzzle, vector<int>& missing_elements)
{
	const int rel_size = puzzle._size + 1;
	bool* ids = new bool[rel_size];
	fill_n(ids, rel_size, false); //initialize with false
	bool double_id = false;

	for (const auto & element : puzzle._elements)
	{
		// assume that each _id has value < puzzle._size (it is checked)
		if (ids[element._id])
		{
			double_id = true;
		}
		ids[element._id] = true;
	}
	for (auto i = 1; i < rel_size; i++)
	{
		if (!ids[i])
		{
			missing_elements.push_back(i);
		}
	}
	return double_id;
}

bool Parser::check_if_valid_and_report_error(const Puzzle& puzzle, ofstream& fout, vector<int>& missing_elements,
                                             vector<int>& wrong_ids, vector<string>& bad_format_lines,
                                             vector<string>& bad_format_ids) const
{
	bool is_valid = true;
	const bool double_id = get_missing_elements(puzzle, missing_elements);

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
		ostringstream oss;
		oss << "Puzzle of _size " << puzzle._size << " cannot have the following IDs: ";
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
			const int id = stoi(delimited[0]);
			fout << "Puzzle ID " << id << " has wrong data: " << line << endl;
		}
	}
	if (!bad_format_ids.empty())
	{
		is_valid = false;
		ostringstream oss;
		oss << "The following element(s) doesn't have a valid ID: ";

		const string last_id = bad_format_ids.back();
		bad_format_ids.pop_back();
		for (const string& id : bad_format_ids)
		{
			oss << id << ", ";
		}
		oss << last_id;
		fout << oss.str() << endl;
	}
	if (double_id)
	{
		is_valid = false;
		fout << "Error: Input contains duplicate IDs" << endl;
	}
	return is_valid;
}

void Parser::get_ids_with_comma_delimiter(vector<int>& elements, ostringstream& oss) const
{
	copy(elements.begin(), elements.end() - 1,
	     ostream_iterator<int>(oss, ", "));

	// Now add the last element with no delimiter
	oss << elements.back();
}

bool Parser::parse(ifstream& fin, Puzzle& puzzle, ofstream& fout) const
{
	string line;
	vector<int> missing_elements;
	vector<int> wrong_ids;
	vector<string> bad_format_lines;
	vector<string> bad_format_ids;
	string msg;
	try
	{
		getline(fin, line);
		clean_spaces(line);
		puzzle._size = process_first_line(line, msg);
		while (getline(fin, line))
		{
			this->process_line(line, wrong_ids, bad_format_lines, bad_format_ids, puzzle._size, puzzle._elements);
		}

		return check_if_valid_and_report_error(puzzle, fout, missing_elements, wrong_ids, bad_format_lines, bad_format_ids);
	}
	catch (exception ex)
	{
		fout << msg << endl;
		return false;
	}
}

int Parser::process_first_line(const string& line, string& msg) const
{
	vector<string> delimited = split(line, '=');
	const string num = delimited[1];
	if (!is_digits(num))
	{
		msg = "invalid number of _elements";
		throw exception();
	}
	return stoi(num);
}

int Parser::parse_edge(const string& edge, string& msg) const
{
	if (!is_digits_with_minus(edge))
	{
		msg = "edge is not a number";
		throw exception();
	}
	const int parsed = stoi(edge);
	if (parsed < -1 || parsed > 1)
	{
		msg = "edge is not valid number";
		throw exception();
	}
	return parsed;
}

bool Parser::is_digits(const string& str)
{
	return all_of(str.begin(), str.end(), ::isdigit);
}

bool Parser::is_digits_with_minus(const string& str)
{
	if (str[0] == '-')
	{
		string str2 = str.substr(1, str.size());
		return all_of(str2.begin(), str2.end(), ::isdigit);
	}
	return all_of(str.begin(), str.end(), ::isdigit);
}

void Parser::process_line(const string& line, vector<int>& wrong_ids, vector<string>& bad_format_lines,
                          vector<string>& bad_format_ids,
                          const int elements_count,
                          vector<Element>& elements) const
{
	vector<string> delimited = split(line, ' ');

	string msg;

	if (!is_digits(delimited[0]))
	{
		bad_format_ids.push_back(delimited[0]);
		return;
	}

	const int id = stoi(delimited[0]);

	if (id > elements_count || id <= 0)
	{
		wrong_ids.push_back(id);
		return;
	}

	try
	{
		const int left = parse_edge(delimited[1], msg);
		const int top = parse_edge(delimited[2], msg);
		const int right = parse_edge(delimited[3], msg);
		const int bottom = parse_edge(delimited[4], msg);

		const Element el(id, left, top, right, bottom);
		elements.push_back(el);
	}
	catch (exception ex)
	{
		bad_format_lines.push_back(line);
		const Element el(id, 0, 0, 0, 0);
		elements.push_back(el);
	}
}

void Parser::clean_spaces(string& str)
{
	str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

//splits string s to a vector
vector<string> Parser::split(const string& s, const char delim) const
{
	vector<string> elems;
	stringstream str_st(s);
	string item;

	while (getline(str_st, item, delim))
	{
		elems.push_back(item); //push_back is a function of vector class, it inserted to the back of the vector.
	}

	return elems;
}
