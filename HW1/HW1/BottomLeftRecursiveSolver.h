#pragma once
#ifndef __BOTTOMLEFTRECURSIVESOLVER_H_INCLUDED__
#define __BOTTOMLEFTRECURSIVESOLVER_H_INCLUDED__   
#include "BaseSolver.h"
#include "Puzzle.h"

class BottomLeftRecursiveSolver :
	public BaseSolver
{
public:
	BottomLeftRecursiveSolver();
	~BottomLeftRecursiveSolver();
	bool solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
	           vector<vector<Element>>& puzzle, vector<Element>& remaining_elements, const bool& finished) override;
protected:
	void sort_elements(vector<Element>& elements) override;
	bool can_be_placed(const int r, const int c, const vector<vector<Element>>& mat,
	                   const Element& element, pair<int, int> dimensions) const override;
	pair<int, int> get_next_indices(const int r, const int c, const pair<int, int> dimensions) const override;
	bool halt_condition(const int r, const int c ,pair<int, int>) const override;
	
};
#endif
