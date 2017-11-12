#include <list>
#include "Puzzle.h"
using namespace std;


	Puzzle::Puzzle(const list<Element>& elements, const list<Element>::iterator& element, unsigned size)
		: elements(elements),
		  it(element),
		  size(size)
	{
	}


