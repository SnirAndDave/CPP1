#pragma once
#ifndef __ISOLVER_H_INCLUDED__
#define __ISOLVER_H_INCLUDED__   
#include <vector>
#include "Element.h"

class ISolver
{
public:
	virtual ~ISolver() = default;
	virtual bool solve(std::pair<int, int>& dimentions, std::vector<std::vector<Element>>& puzzle,
	                   std::vector<Element>& remaining_elements) = 0;
};

class RecursiveSolver : public ISolver
{
public:

	bool solve(std::pair<int, int>& dimentions, std::vector<std::vector<Element>>& puzzle,
		std::vector<Element>& remaining_elements) override;
};
#endif
