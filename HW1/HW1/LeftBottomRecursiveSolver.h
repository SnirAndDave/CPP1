#pragma once
#ifndef __LEFTBOTTOMRECURSIVESOLVER_H_INCLUDED__
#define __LEFTBOTTOMRECURSIVESOLVER_H_INCLUDED__   
#include "BaseSolver.h"

class LeftBottomRecursiveSolver :
	public BaseSolver
{
public:
	LeftBottomRecursiveSolver();
	~LeftBottomRecursiveSolver();
	bool solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
	           vector<vector<Element>>& puzzle, vector<Element>& remaining_elements, const bool& finished) override;
	static bool can_be_placed(const int r, const int c, const pair<int, int>& dimensions, const vector<vector<Element>>& mat,
	                   const Element& element);
protected:
	void sort_elements(vector<Element>& elements) override;
private:

	bool rec_solve(int r, int c, const bool is_rotation_enabled, pair<int, int>& dimensions,
	               vector<vector<Element>>& mat, vector<Element>& remaining_elements, const bool& finished) const;
};
#endif
