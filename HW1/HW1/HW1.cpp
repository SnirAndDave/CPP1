#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Puzzle.cpp"

using namespace std;





class Parser {
public:
	void parse(const string& filePath, Puzzle puzzle) {
		puzzle.elements.clear();//clears the vector
		ifstream fin(filePath); //creating an ifstream object and opening file in path attackPath 
		string line;
		while (getline(fin, line)) //getline returns null if we get to end of file.
		{
			Element elem = this->processLine(line);
			puzzle.elements.insert(elem);
		}
	}

	Element& processLine(const string& line) {

	}


private:


};

int main()
{
	Puzzle puzzle;

	return 0;
}