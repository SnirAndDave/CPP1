#pragma once
#ifndef __BOTTOMRIGHTRECURSIVESOLVER_H_INCLUDED__
#define __BOTTOMRIGHTRECURSIVESOLVER_H_INCLUDED__   
#include "BaseSolver.h"
#include "Puzzle.h"

class BottomRightRecursiveSolver :
	public BaseSolver
{
public:
	BottomRightRecursiveSolver();
	~BottomRightRecursiveSolver();
	bool solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
	           vector<vector<Element>>& puzzle, vector<Element>& remaining_elements, const bool& finished) override;
protected:
	void sort_elements(vector<Element>& elements) override;
	static bool can_be_placed(int r, int c, const pair<int, int>& dimensions, const vector<vector<Element>>& mat,
	                   const Element& element);
private:

	bool rec_solve(int r, int c, const bool is_rotation_enabled, pair<int, int>& dimensions,
	               vector<vector<Element>>& mat, vector<Element>& remaining_elements, const bool& finished) const;
};
#endif
