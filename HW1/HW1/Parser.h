#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Puzzle.cpp"
#include <vector>
#include <algorithm>

using namespace std;

#ifndef __PARSER_H_INCLUDED__   
#define __PARSER_H_INCLUDED__


class Parser
{
public:
	void parse(const string& filePath, Puzzle& puzzle);
	
	int processFirstLine(const string& line);


	Element processLine(const string& line);
	void cleanSpaces(string& str);
	std::vector<std::string> split(const std::string &s, char delim);
	
private:
};

#endif

