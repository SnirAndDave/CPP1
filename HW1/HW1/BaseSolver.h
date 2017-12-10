#pragma once
#ifndef __BASESOLVER_H_INCLUDED__   
#define __BASESOLVER_H_INCLUDED__   
#include <utility>
#include <vector>
#include "Element.h"

using namespace std;

class BaseSolver
{
public:
	BaseSolver();
	virtual ~BaseSolver();
	virtual bool solve(pair<int, int>& dimentions, vector<std::vector<Element>>& puzzle,
		std::vector<Element>& remaining_elements) = 0;
protected:
	virtual bool can_be_placed(int r, int c, const pair<int, int>& dimensions, const vector<vector<Element>>& mat, const Element& element);
};

#endif