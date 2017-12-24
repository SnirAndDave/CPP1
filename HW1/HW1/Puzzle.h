#pragma once
#ifndef __PUZZLE_H_INCLUDED__
#define __PUZZLE_H_INCLUDED__
#include <fstream>
#include <vector>
#include <memory>
#include "BaseSolver.h"
#include <thread>
#include <mutex>
#include <atomic>

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
	Puzzle(ofstream& fout, bool rotation, int thread_cnt)
		: _is_rotation_enabled(rotation), _fout(fout), _finished(false), _solved(false)
	{
		_size = 0;
		_thread_cnt = thread_cnt > 9 ? 9 : thread_cnt;
	}

	void print_solution(const vector<vector<Element>>& matrix) const;
	static vector<vector<Element>> create_empty_mat(const pair<int, int>& dimensions);
	vector<shared_ptr<BaseSolver>> choose_solver();
	void solve();
	static Element get_element(const vector<vector<Element>>& mat, int r, int c);
	static void print_solution_to_console(const vector<vector<Element>>& matrix);
	vector<Element> _elements;
	int _size;
	bool _is_rotation_enabled;
private:
	void set_solution(const vector<vector<Element>>& mat, bool solved);
	void thread_solve(pair<int, int> row_col_pair, const shared_ptr<BaseSolver>& solver);
	vector<pair<int, int>> size_to_matrices() const;
	int get_straight_edges_count();
	vector<pair<int, int>> get_valid_dimensions(vector<pair<int, int>> dimensions); // straight edges
	vector<vector<vector<Element>>> create_all_permutations_of_dimension(pair<int, int> dimensions) const;
	static vector<vector<Element>> vector_to_mat(vector<Element> copy, pair<int, int> dimensions);
	static bool verify_matrix(vector<vector<Element>> mat);
	vector<Corner> find_missing_corners();
	bool validate_sum_of_edges();
	int _thread_cnt;
	ofstream& _fout;
	mutex _mutex;
	condition_variable _cv;
	bool _finished;
	bool _solved;
	vector<vector<Element>> _solution;
};


#endif
