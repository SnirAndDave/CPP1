#pragma once
#ifndef __LEFTRECURSIVESOLVER_H_INCLUDED__
#define __LEFTRECURSIVESOLVER_H_INCLUDED__   
#include "BaseSolver.h"

class LeftBottomRecursiveSolver :
	public BaseSolver
{
public:
	LeftBottomRecursiveSolver();
	~LeftBottomRecursiveSolver();
	bool solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
	           vector<vector<Element>>& puzzle, vector<Element>& remaining_elements) override;
	static bool can_be_placed(const int r, const int c, const pair<int, int>& dimensions, const vector<vector<Element>>& mat,
	                   const Element& element);
protected:
	void sort_elements(vector<Element>& elements) override;
private:

	bool rec_solve(int r, const bool is_rotation_enabled, int c, pair<int, int>& dimensions,
	               vector<vector<Element>>& mat, vector<Element>& remaining_elements) const;
};
#endif
