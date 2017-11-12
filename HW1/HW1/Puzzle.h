#pragma once
#ifndef __PUZZLE_H_INCLUDED__   
#define __PUZZLE_H_INCLUDED__
#include "Element.h"
#include <list>
#include <vector>
using namespace std;
class  Puzzle
{
public:

	std::vector<Element> elements;
	unsigned int size;
};


#endif
