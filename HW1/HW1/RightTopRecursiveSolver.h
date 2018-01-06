#pragma once
#ifndef __RIGHTTOPRECURSIVESOLVER_H_INCLUDED__
#define __RIGHTTOPRECURSIVESOLVER_H_INCLUDED__   
#include "BaseSolver.h"
#include "Puzzle.h"

class RightTopRecursiveSolver :
	public BaseSolver
{
public:
	RightTopRecursiveSolver();
	~RightTopRecursiveSolver();
	bool solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
	           vector<vector<Element>>& puzzle, vector<Element>& remaining_elements, const bool& finished) override;
protected:
	void sort_elements(vector<Element>& elements) override;

	bool can_be_placed(const int r, const int c, const vector<vector<Element>>& mat, const Element& element,
		pair<int, int>) const override;
	bool halt_condition(const int, const int, pair<int, int>) const override;
	pair<int, int> get_next_indices(const int r, const int c, const pair<int, int>) const override;
};
#endif
