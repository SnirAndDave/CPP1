#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Parser.h"

using namespace std;


void Parser::getMissingElements(const Puzzle& puzzle, vector<int>& missingElements)
{
	bool* ids = new bool[puzzle.size + 1];
	bool isMissing = false;
	for (auto it = puzzle.elements.begin(); it != puzzle.elements.end(); ++it)
	{
		// assume that each id has value < puzzle.size (it is checked)
		ids[it->id] = true;
	}
	for (int i = 1; i < puzzle.size + 1; i++)
	{
		if (!ids[i])
		{
			isMissing = true;
			missingElements.push_back(i);
		}
	}
}

bool Parser::parse(ifstream& fin, Puzzle& puzzle, ofstream& fout)
{
	string line;
	vector<int> missing_elements;
	vector<int> wrong_ids;
	vector<string> badFormatLines;

	try
	{
		getline(fin, line);
		cleanSpaces(line);
		puzzle.size = processFirstLine(line);

		for (int i = 0; i < puzzle.size; i++)
		{
			// missing elements
			if (!getline(fin, line))
			{
				break;
			}
			this->processLine(line, wrong_ids, badFormatLines, puzzle.size, puzzle.elements);
		}
		getMissingElements(puzzle, missing_elements);

		return true;
	}
	catch (exception ex)
	{
		fout << "Failed to parse input file - with exception:";
		cout << ex.what();
		return false;
	}
}

int Parser::processFirstLine(const string& line)
{
	vector<string> delimited = split(line, '=');
	// todo error handling 
	return stoi(delimited.at(1));
}

int Parser::parseEdge(string edge)
{
	int parsed = stoi(edge);
	if (parsed < -1 || parsed > 1)
	{
		throw exception("edge is not valid");
	}
	return parsed;
}

void Parser::processLine(const string& line, vector<int>& wrong_ids, vector<string>& wrong_lines, int elementsCount,
                         vector<Element>& elements)
{
	try
	{
		vector<string> delimited = split(line, ' ');
		int id = stoi(delimited[0]);
		if (id > elementsCount || id < 0)
		{
			wrong_ids.push_back(id);
			return;
		}
		int left = stoi(delimited[1]);
		int top = stoi(delimited[2]);
		int right = stoi(delimited[3]);
		int bottom = stoi(delimited[4]);

		Element el(id, left, top, right, bottom);
		elements.push_back(el);
	}
	catch (exception ex)
	{
		wrong_lines.push_back(line);
	}
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
