#pragma once
#ifndef __PUZZLE_H_INCLUDED__
#define __PUZZLE_H_INCLUDED__
#include <fstream>
#include <vector>
#include <memory>
#include "BaseSolver.h"

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
		: _is_rotation_enabled(rotation), _m_fout(fout)
	{
		_size = 0;
	}

	void print_solution(const vector<vector<Element>>& matrix) const;
	static vector<vector<Element>> create_empty_mat(const pair<int, int>& dimensions);
	unique_ptr<BaseSolver> choose_solver();
	void solve();
	static Element get_element(const vector<vector<Element>>& mat, int r, int c);
	static void print_solution_to_console(const vector<vector<Element>>& matrix);
	vector<Element> _elements;
	int _size;
	bool _is_rotation_enabled;
private:
	vector<pair<int, int>> size_to_matrices() const;
	int get_straight_edges_count();
	vector<pair<int, int>> get_valid_dimensions(vector<pair<int, int>> dimentions); // straight edges
	vector<vector<vector<Element>>> create_all_permutations_of_dimension(pair<int, int> dimentions) const;
	static vector<vector<Element>> vector_to_mat(vector<Element> copy, pair<int, int> dimentions);
	static bool verify_matrix(vector<vector<Element>> mat);
	vector<Corner> find_missing_corners();
	bool validate_sum_of_edges();
	
	ofstream& _m_fout;
};


#endif
