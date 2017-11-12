#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Parser.h"
#include <iterator>

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
	for (auto i = 1; i < puzzle.size + 1; i++)
	{
		if (!ids[i])
		{
			isMissing = true;
			missingElements.push_back(i);
		}
	}
}

bool Parser::checkIfValidAndReportError(const Puzzle& puzzle, ofstream& fout, vector<int>& missing_elements,
                                        vector<int>& wrong_ids, vector<string>& badFormatLines)
{
	bool isValid = true;
	getMissingElements(puzzle, missing_elements);
	if (!missing_elements.empty())
	{
		std::ostringstream oss;
		oss << "Missing puzzle element(s) with the following IDs: ";
		isValid = false;
		copy(missing_elements.begin(), missing_elements.end() - 1,
		     ostream_iterator<int>(oss, ", "));

		// Now add the last element with no delimiter
		oss << missing_elements.back();
		fout << oss.str() << endl;
	}
	if (!wrong_ids.empty())
	{
		std::ostringstream oss;
		oss << "Puzzle of size <" << puzzle.size << "> cannot have the following IDs:";
		isValid = false;
		copy(wrong_ids.begin(), wrong_ids.end() - 1,
		     ostream_iterator<int>(oss, ", "));

		// Now add the last element with no delimiter
		oss << wrong_ids.back();
		fout << oss.str() << endl;
	}
	if (!badFormatLines.empty())
	{
		isValid = false;
		for (auto const& line : badFormatLines)
		{
			vector<string> delimited = split(line, ' ');
			int id = stoi(delimited[0]);
			fout << "Puzzle ID <" << id << "> has wrong data: " << line;
		}
	}
	return isValid;
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

		for (auto i = 0; i < puzzle.size; i++)
		{
			// missing elements
			if (!getline(fin, line))
			{
				break;
			}
			this->processLine(line, wrong_ids, badFormatLines, puzzle.size, puzzle.elements);
		}

		return checkIfValidAndReportError(puzzle, fout, missing_elements, wrong_ids, badFormatLines);
	}
	catch (exception ex)
	{
		fout << "Failed to parse input file - with exception:" << endl;
		cout << ex.what() << endl;
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
		int left = parseEdge(delimited[1]);
		int top = parseEdge(delimited[2]);
		int right = parseEdge(delimited[3]);
		int bottom = parseEdge(delimited[4]);
		if (delimited.size() > 5)
		{
			throw exception("more than 4 edges");
		}
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
