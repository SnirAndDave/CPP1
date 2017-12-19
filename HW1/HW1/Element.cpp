#include "Element.h"

Element::Element(int id, int left, int top, int right, int down)
	: _id(id),
	  _left(left),
	  _top(top),
	  _right(right),
	  _bottom(down),
	  _rotation(0)
{
}

Element::Element()
	: _id(),
	  _left(),
	  _top(),
	  _right(),
	  _bottom(),
	  _rotation(0)
{
}

int Element::rotation() const
{
	return _rotation;
}

void Element::rotate_right()
{
	const int temp_left = _left;
	_left = _bottom;
	_bottom = _right;
	_right = _top;
	_top = temp_left;
	_rotation = (_rotation + 90) % 360;
}
