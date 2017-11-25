#pragma once
#include <sstream>
#include "Puzzle.h"
#include <vector>


using namespace std;

#ifndef __PARSER_H_INCLUDED__
#define __PARSER_H_INCLUDED__


class Parser
{
public:
	bool get_missing_elements(const Puzzle& puzzle, vector<int>& missingElements);
	bool check_if_valid_and_report_error(const Puzzle& puzzle, ofstream& fout, vector<int>& missing_elements,
	                                     vector<int>& wrong_ids, vector<string>& bad_format_lines,
	                                     vector<string>& bad_format_ids);
	void get_ids_with_comma_delimiter(vector<int>& elements, ostringstream& oss);
	bool parse(ifstream& fin, Puzzle& puzzle, ofstream& fout);

	int process_first_line(const string& line, string& msg);
	int parse_edge(string edge, string& msg);
	bool is_digits(const string& str);
	bool is_digits_with_minus(const string& str);


	void processLine(const string& line, vector<int>& wrong_ids, vector<string>& bad_format_lines,
	                 vector<string>& bad_format_ids, int
	                 elements_count, vector<Element>& elements);
	void clean_spaces(string& str);
	vector<string> split(const string& s, char delim);

private:
};

#endif
