#include "Element.h"

Element::Element(int id, int left, int top, int right, int down)
	: id(id),
	  left(left),
	  top(top),
	  right(right),
	  bottom(down),
	  rotation_(0)
{
}

Element::Element()
	: id(),
	  left(),
	  top(),
	  right(),
	  bottom(),
	  rotation_(0)
{
}

int Element::rotation() const
{
	return rotation_;
}

void Element::rotate_right()
{
	int temp_left = left;
	left = bottom;
	bottom = right;
	right = top;
	top = temp_left;
	rotation_ = (rotation_ + 90) % 360;
}
