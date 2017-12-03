#pragma once
#ifndef __PUZZLE_H_INCLUDED__
#define __PUZZLE_H_INCLUDED__
#include "Element.h"
#include <fstream>
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
	Puzzle(ofstream& fout, bool rotation)
		: m_fout(fout), is_rotation_enabled(rotation)
	{
		size = 0;
	}

	void print_solution(const vector<vector<Element>>& vector);
	vector<vector<Element>> create_empty_mat(const pair<int, int>& pair);
	void solve();
	bool can_be_placed(int i, int c, const pair<int, int>& pair, const vector<vector<Element>>& mat, const Element& element);
	vector<Element> elements;
	int size;
	bool is_rotation_enabled;
private:
	vector<pair<int, int>> size_to_matrices();
	int get_straight_edges_count();
	vector<pair<int, int>> get_valid_dimentions(vector<pair<int, int>> dimentions); // straight edges
	vector<vector<vector<Element>>> create_all_permutations_of_dimention(pair<int, int> dimentions);
	vector<vector<Element>> vector_to_mat(vector<Element> copy, pair<int, int> dimentions);
	Element getElement(const vector<vector<Element>> mat, int i, int r);
	bool verify_matrix(vector<vector<Element>> mat);
	bool rec_solve(int r, int c, pair<int, int>& dimentions, vector<vector<Element>>& mat,
	               vector<Element> remaining_elements);
	vector<Corner> find_missing_corners();
	bool validate_sum_of_edges();
	ofstream& m_fout;
};


#endif
