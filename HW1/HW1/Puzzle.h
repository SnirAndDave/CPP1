#pragma once
#ifndef __PUZZLE_H_INCLUDED__
#define __PUZZLE_H_INCLUDED__
#include "Element.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;
enum Corner
{
	TL,
	TR,
	BL,
	BR
};

class Puzzle
{
public:
	bool validate();
	void solve();
	vector<Element> elements;
	unsigned int size;
private:

	bool validate_corner_elements();
	bool validate_sum_of_edges(ofstream& fout);
	ofstream m_out_file;
	ofstream& fout;
};


#endif
