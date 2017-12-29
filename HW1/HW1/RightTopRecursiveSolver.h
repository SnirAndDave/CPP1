#pragma once
#ifndef __RIGHTRECURSIVESOLVER_H_INCLUDED__
#define __RIGHTRECURSIVESOLVER_H_INCLUDED__   
#include "BaseSolver.h"
#include "Puzzle.h"

class RightTopRecursiveSolver :
	public BaseSolver
{
public:
	RightTopRecursiveSolver();
	~RightTopRecursiveSolver();
	bool solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
	           vector<vector<Element>>& puzzle, vector<Element>& remaining_elements) override;
protected:
	void sort_elements(vector<Element>& elements) override;
	static bool can_be_placed(int r, int c, const pair<int, int>& dimensions, const vector<vector<Element>>& mat,
	                          const Element& element);
private:

	bool rec_solve(int r, const bool is_rotation_enabled, int c, pair<int, int>& dimensions,
	               vector<vector<Element>>& mat, vector<Element>& remaining_elements) const;
};
#endif
