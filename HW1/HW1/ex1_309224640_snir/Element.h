#pragma once
#ifndef __ELEMENT_H_INCLUDED__   
#define __ELEMENT_H_INCLUDED__   

class Element {
	friend bool operator<(const Element& lhs, const Element& rhs)
	{
		return lhs.id < rhs.id;
	}

	friend bool operator<=(const Element& lhs, const Element& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const Element& lhs, const Element& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const Element& lhs, const Element& rhs)
	{
		return !(lhs < rhs);
	}

public:
	Element(int id, int left, int top, int right, int down);
	
	int id;
	int left;
	int top;
	int right;
	int bottom;
};
#endif