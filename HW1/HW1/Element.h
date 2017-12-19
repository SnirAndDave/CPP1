#pragma once
#ifndef __ELEMENT_H_INCLUDED__
#define __ELEMENT_H_INCLUDED__   

class Element
{
	friend bool operator<(const Element& lhs, const Element& rhs)
	{
		return lhs._id < rhs._id;
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

	friend bool operator==(const Element& lhs, const Element& rhs)
	{
		return lhs._id == rhs._id;
	}

	friend bool operator!=(const Element& lhs, const Element& rhs)
	{
		return !(lhs == rhs);
	}

public:
	Element(int id, int left, int top, int right, int down);
	Element();
	int rotation() const;
	void rotate_right();
	int _id;
	int _left;
	int _top;
	int _right;
	int _bottom;
private:
	int _rotation;
};
#endif
