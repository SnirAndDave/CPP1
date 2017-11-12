#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Parser.h"

using namespace std;


void Parser::parse(const string& filePath, Puzzle& puzzle)
{
	puzzle.it = puzzle.elements.begin();
	ifstream fin(filePath); //creating an ifstream object and opening file in path attackPath 
	string line;

	//get first line
	getline(fin, line);
	cleanSpaces(line);
	puzzle.size = processFirstLine(line);

	//read rest of file
	while (getline(fin, line)) //getline returns null if we get to end of file.
	{
		Element elem = this->processLine(line);
		puzzle.elements.insert(puzzle.it, elem);
	}
}

int Parser::processFirstLine(const string& line)
{
	vector<string> delimited = split(line, '=');
	// todo error handling 
	return stoi(delimited.at(1));
}

Element Parser::processLine(const string& line)
{
	vector<string> delimited = split(line, ' ');
	int id = stoi(delimited[0]);
	int left = stoi(delimited[1]);
	int top = stoi(delimited[2]);
	int right = stoi(delimited[3]);
	int bottom = stoi(delimited[4]);
	Element el(id, left, top, right, bottom);
}

void Parser::cleanSpaces(string& str)
{
	string::iterator end_pos = remove(str.begin(), str.end(), ' ');
}

//splits string s to a vector
vector<string> Parser::split(const string& s, char delim)
{
	vector<string> elems;
	stringstream strSt(s);
	string item;

	while (getline(strSt, item, delim)) //we could ommit the '' notion from here.
	{
		elems.push_back(item); //push_back is a function of vector class, it inserted to the back of the vector.
	}

	return elems;
}
