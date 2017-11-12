#pragma once
#ifndef __PUZZLE_H_INCLUDED__   
#define __PUZZLE_H_INCLUDED__
#include "Element.h"
#include <list>
using namespace std;
class  Puzzle
{
public:
	Puzzle::Puzzle(const list<Element>& elements, const list<Element>::iterator& element, unsigned size);

	std::list<Element> elements;
	std::list<Element>::iterator it;
	unsigned int size;
};


#endif
