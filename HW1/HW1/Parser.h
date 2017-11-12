#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Puzzle.h"
#include <vector>
#include <algorithm>

using namespace std;

#ifndef __PARSER_H_INCLUDED__   
#define __PARSER_H_INCLUDED__


class Parser
{
public:
	void getMissingElements(const Puzzle& puzzle, vector<int>& missingElements);
	bool checkIfValidAndReportError(const Puzzle& puzzle, ofstream& fout, vector<int>& missing_elements,
		 vector<int>& wrong_ids, vector<string>& badFormatLines);
	bool parse(ifstream& fin, Puzzle& puzzle, ofstream& fout);
	
	int processFirstLine(const string& line);
	int parseEdge(string edge);


	void processLine(const string& line, vector<int>& wrong_ids, vector<string>& wrong_lines, int elementsCount, vector<Element>& elements);
	void cleanSpaces(string& str);
	std::vector<std::string> split(const std::string &s, char delim);
	
private:

};

#endif

