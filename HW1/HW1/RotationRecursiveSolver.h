#pragma once
#ifndef __ROTATIONRECURSIVESOLVER_H_INCLUDED__
#define __ROTATIONRECURSIVESOLVER_H_INCLUDED__   
#include "BaseSolver.h"

class RotationRecursiveSolver :
	public BaseSolver
{
public:
	RotationRecursiveSolver();
	~RotationRecursiveSolver();
	bool solve(pair<int, int>& dimentions, vector<vector<Element>>& puzzle,
	           vector<Element>& remaining_elements) override;

private:

	bool rec_solve(int r, int c, pair<int, int>& dimensions, vector<vector<Element>>& mat,
	               vector<Element>& remaining_elements);
};

#endif
