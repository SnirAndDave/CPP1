#include <list>
#include "Element.cpp"
using namespace std;

class  Puzzle
{
public:
	list<Element> elements;
	list<Element>::iterator it;
	unsigned int size;
};