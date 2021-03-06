#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Parser.h"
#include <iterator>
#include <cctype>

using namespace std;

namespace
{
	struct ParserErrorCategory : std::error_category
	{
		const char* name() const noexcept override;
		std::string message(int env) const override;
	};

	const char* ParserErrorCategory::name() const noexcept
	{
		return "Parse Errors";
	}

	std::string ParserErrorCategory::message(int env) const
	{
		switch (static_cast<ParserErrorCode>(env))
		{
		case ParserErrorCode::parse_arguments_error:
			return "could not parse arguments properly";

		case ParserErrorCode::open_file_error:
			return "Could not open file";

		case ParserErrorCode::invalid_number_of_elements_error:
			return "invalid number of elements in first line";

		case ParserErrorCode::missing_elements_error:
			return "missing elements in input file";

		case ParserErrorCode::wrong_id_error:
			return "puzzle of given size cannot have this ID";

		case ParserErrorCode::bad_format_id_error:
			return "invalid element ID";

		case ParserErrorCode::bad_format_data_error:
			return "element received with invalid data";

		case ParserErrorCode::duplicate_ids_error:
			return "input contains duplicate IDs";

		default:
			return "(unrecognized error)";
		}
	}

	const ParserErrorCategory theParserErrorCategory{};
}

std::error_code make_error_code(ParserErrorCode e)
{
	return {static_cast<int>(e), theParserErrorCategory};
}


/**
* Checks if given flag exists in cmd line
*/
bool Parser::cmdOptionExists(vector<string> vec, const std::string& option)
{
	return std::find(vec.begin(), vec.end(), option) != vec.end();
}

/**
* Returns index of given flag in cmd line
*/
int Parser::cmdOptionIndex(vector<string> vec, const std::string& option)
{
	const auto it = std::find(vec.begin(), vec.end(), option);
	if (it == vec.end())
	{
		return -1;
	}
	const auto index = std::distance(vec.begin(), it);
	return index;
}

string Parser::getCmdOption(vector<string> vec, const std::string& option)
{
	return vec[cmdOptionIndex(vec, option)];
}

/**
* Parse arguments from command line. Handles the flags -rotate and -threads
*/
void Parser::parse_arguments(const int argc, char* argv[])
{
	const string rotate = "-rotate";
	const string threads = "-threads";
	vector<string> argv_vec(argv, argv + argc);
	if (argc == 3)
	{
		_fin_path = argv_vec[1];
		_fout_path = argv_vec[2];
		return;
	}
	if (cmdOptionExists(argv_vec, rotate))
	{
		_rotation_enabled = true;
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
			_thread_cnt = stoi(argv_vec[index + 1]);
		}
		catch (exception ex)
		{
			cout << "usage: -threads THREAD_COUNT" << endl;
			throw invalid_argument(threads);
		}
		argv_vec.erase(argv_vec.begin() + index + 1);
		argv_vec.erase(argv_vec.begin() + index);
	}
	_fin_path = argv_vec[1];
	_fout_path = argv_vec[2];
}


/**
 * Checks if all IDs exist in elements, from 1 to NumElements given in first line
 * Adds missing elements to a vector to be used later
 */
bool Parser::get_missing_elements(const Puzzle& puzzle, vector<int>& missing_elements)
{
	const int rel_size = puzzle._size + 1;
	bool* ids = new bool[rel_size];
	fill_n(ids, rel_size, false); //initialize with false
	bool double_id = false;

	for (const auto& element : puzzle._elements)
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

/**
 * This function checks all vectors with 'bad' info, in the order that is instructed from Ex 1.
 * Responsible for printing the errors into output file, updating error code, and update calling function that input is valid or not
 */
bool Parser::check_if_valid_and_report_error(const Puzzle& puzzle, ofstream& fout, vector<int>& missing_elements,
                                             vector<int>& wrong_ids, vector<string>& bad_format_lines,
                                             vector<string>& bad_format_ids, ParserErrorCode* ec) const
{
	bool is_valid = true;
	const bool double_id = get_missing_elements(puzzle, missing_elements);

	if (!missing_elements.empty())
	{
		ostringstream oss;
		oss << "Missing puzzle element(s) with the following IDs: ";
		is_valid = false;

		get_ids_with_comma_delimiter(missing_elements, oss);
		*ec = ParserErrorCode::missing_elements_error;
		fout << oss.str() << endl;
	}
	if (!wrong_ids.empty())
	{
		ostringstream oss;
		oss << "Puzzle of size " << puzzle._size << " cannot have the following IDs: ";
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
		*ec = ParserErrorCode::duplicate_ids_error;
		fout << "Error: " << make_error_code(*ec).message() << endl;
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

bool Parser::parse(ifstream& fin, Puzzle& puzzle, ofstream& fout, ParserErrorCode* ec) const
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
		//1. Parse first line and receive puzzle size
		puzzle._size = process_first_line(line, msg, ec);
		while (getline(fin, line))
		{
			//2. Parse every line and update all 'bad' info vectors + puzzle elements
			this->process_line(line, wrong_ids, bad_format_lines, bad_format_ids, puzzle._size, puzzle._elements, ec);
		}

		//3. Check if all is ok and program can start solving puzzle
		return check_if_valid_and_report_error(puzzle, fout, missing_elements, wrong_ids, bad_format_lines, bad_format_ids,
		                                       ec);
	}
		//not using actual exception, msg already contains the exception message and will print to output file
	catch (exception ex)
	{
		fout << msg << endl;
		return false;
	}
}


int Parser::process_first_line(const string& line, string& msg, ParserErrorCode* ec) const
{
	vector<string> delimited = split(line, '=');
	const string num = delimited[1];
	if (!is_digits(num))
	{
		*ec = ParserErrorCode::invalid_number_of_elements_error;
		msg = make_error_code(*ec).message();
		throw exception();
	}
	return stoi(num);
}

int Parser::parse_edge(const string& edge) const
{
	if (!is_digits_with_minus(edge))
	{
		throw exception();
	}
	const int parsed = stoi(edge);
	if (parsed < -1 || parsed > 1)
	{
		throw exception();
	}
	return parsed;
}

bool Parser::is_digits(const string& str)
{
	return all_of(str.begin(), str.end(), ::isdigit);
}

/**
 * Checks if str is '-<digits>'
 */
bool Parser::is_digits_with_minus(const string& str)
{
	if (str[0] == '-')
	{
		string str2 = str.substr(1, str.size());
		return all_of(str2.begin(), str2.end(), ::isdigit);
	}
	return all_of(str.begin(), str.end(), ::isdigit);
}

/**
 * Parses each line of element and gets element's ID and edges.
 * Inserts into vectors whenever an error appears in the input, these vectors are used later
 */
void Parser::process_line(const string& line, vector<int>& wrong_ids, vector<string>& bad_format_lines,
                          vector<string>& bad_format_ids,
                          const int elements_count,
                          vector<Element>& elements, ParserErrorCode* ec) const
{
	vector<string> delimited = split(line, ' ');

	string msg;

	//check element id format
	if (!is_digits(delimited[0]))
	{
		*ec = ParserErrorCode::bad_format_id_error;
		bad_format_ids.push_back(delimited[0]);
		return;
	}

	const int id = stoi(delimited[0]);

	//check if possible id with puzzle size
	if (id > elements_count || id <= 0)
	{
		*ec = ParserErrorCode::wrong_id_error;
		wrong_ids.push_back(id);
		return;
	}

	//parse element's edges
	try
	{
		const int left = parse_edge(delimited[1]);
		const int top = parse_edge(delimited[2]);
		const int right = parse_edge(delimited[3]);
		const int bottom = parse_edge(delimited[4]);

		const Element el(id, left, top, right, bottom);
		elements.push_back(el);
	}
		//not using actual exception, adding bad line to vector and message will be printed later
	catch (exception ex)
	{
		bad_format_lines.push_back(line);
		*ec = ParserErrorCode::bad_format_data_error;
		msg = make_error_code(*ec).message();
		const Element el(id, 0, 0, 0, 0);
		elements.push_back(el);
	}
}

void Parser::clean_spaces(string& str)
{
	str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}

/**
 *splits string s to a vector
 **/
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
