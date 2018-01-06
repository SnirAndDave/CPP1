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
	/**
	* sorts the unused elements, and calls rec_solve while giving start coordinates
	*/
	virtual bool solve(pair<int, int>& dimensions, const bool is_rotation_enabled,
	                   vector<vector<Element>>& puzzle, vector<Element>& remaining_elements, const bool& finished) = 0;
protected:
	virtual bool can_be_placed(const int r, const int c, const vector<vector<Element>>& mat,
	                           const Element& element, pair<int, int> ) const =0;
	/**
	* Sorts the unused elements to make the solver run quicker
	* It takes into consideration the relevant edges with the start or end of the puzzle frame side
	*/
	virtual void sort_elements(vector<Element>& elements);
	/**
	* Checks whether the halting condition is true
	*/
	virtual bool halt_condition(const int , const int, pair<int,int>) const = 0;
	/**
	* Gets the next row and col indices for the next iteration
	*/
	virtual pair<int, int> get_next_indices(const int r, const int c, const pair<int,int> ) const =0;

	bool rec_solve(const int r, const int c, const bool is_rotation_enabled, pair<int, int>& dimensions,
	               vector<vector<Element>>& mat, vector<Element>& remaining_elements, const bool& finished) const;
};

#endif
