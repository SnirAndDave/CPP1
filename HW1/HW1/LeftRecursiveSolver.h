#pragma once
#ifndef __LEFTRECURSIVESOLVER_H_INCLUDED__
#define __LEFTRECURSIVESOLVER_H_INCLUDED__   
#include "BaseSolver.h"

class LeftRecursiveSolver :
	public BaseSolver
{
public:
	LeftRecursiveSolver();
	~LeftRecursiveSolver();
	bool solve(pair<int, int>& dimentions, vector<vector<Element>>& puzzle,
	           vector<Element>& remaining_elements) override;
protected:
	void sort_elements(vector<Element>& elements) override;
private:

	bool rec_solve(int r, int c, pair<int, int>& dimensions, vector<vector<Element>>& mat,
	               vector<Element>& remaining_elements);
};
#endif
