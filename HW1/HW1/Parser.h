#pragma once
#ifndef __PARSER_H_INCLUDED__
#define __PARSER_H_INCLUDED__
#include <sstream>
#include "Puzzle.h"
#include <vector>

using namespace std;

enum class ParserErrorCode
{
	no_errors,
	open_file_error,
	parse_arguments_error,
	invalid_arguments_error,
	invalid_number_of_elements_error,
	missing_elements_error,
	wrong_id_error,
	bad_format_id_error,
	bad_format_data_error,
	duplicate_ids_error,
};

namespace std
{
	template <>
	struct is_error_code_enum<ParserErrorCode> : true_type
	{
	};
}

std::error_code make_error_code(ParserErrorCode);

class Parser
{
public:
	static bool get_missing_elements(const Puzzle& puzzle, vector<int>& missing_elements);
	bool check_if_valid_and_report_error(const Puzzle& puzzle, ofstream& fout, vector<int>& missing_elements,
	                                     vector<int>& wrong_ids, vector<string>& bad_format_lines,
	                                     vector<string>& bad_format_ids, ParserErrorCode* ec) const;
	void get_ids_with_comma_delimiter(vector<int>& elements, ostringstream& oss) const;
	bool parse(ifstream& fin, Puzzle& puzzle, ofstream& fout, ParserErrorCode* ec) const;

	int process_first_line(const string& line, string& msg, ParserErrorCode* ec) const;
	int parse_edge(const string& edge, string& msg) const;
	static bool is_digits(const string& str);
	static bool is_digits_with_minus(const string& str);


	void process_line(const string& line, vector<int>& wrong_ids, vector<string>& bad_format_lines,
	                  vector<string>& bad_format_ids, int
	                  elements_count, vector<Element>& elements, ParserErrorCode* ec) const;
	static void clean_spaces(string& str);
	vector<string> split(const string& s, char delim) const;

private:
};

#endif
