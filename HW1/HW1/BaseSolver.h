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
	virtual bool solve(pair<int, int>& dimentions, vector<vector<Element>>& puzzle,
	                   vector<Element>& remaining_elements) = 0;
protected:
	virtual void sort_elements(vector<Element>& elements);
	virtual bool can_be_placed(int r, int c, const pair<int, int>& dimensions, const vector<vector<Element>>& mat,
	                           const Element& element);
};

#endif
