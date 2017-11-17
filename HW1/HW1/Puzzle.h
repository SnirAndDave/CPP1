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
	void solve();
	vector<Element> elements;
	unsigned int size;
private:
	vector<pair<int, int>> get_valid_dimentions(vector<pair<int, int>> dimentions); // straight edges
	vector<pair<int,int>> size_to_matrices();
	vector<Element**> create_all_permutations_of_dimention(pair<int,int> dimentions);
	bool verify_matrix(Element** mat, pair<int, int> dimention);
	vector<Corner> find_missing_corners();
	bool validate_sum_of_edges();
	ofstream m_out_file;
	ofstream& fout;
};


#endif
