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
	virtual bool solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
	                   vector<vector<Element>>& puzzle, vector<Element>& remaining_elements) = 0;
protected:
	virtual void sort_elements(vector<Element>& elements);
};

#endif
