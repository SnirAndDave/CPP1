#pragma once
#ifndef __ELEMENT_H_INCLUDED__   
#define __ELEMENT_H_INCLUDED__   

class Element {
public:
	Element::Element(int id, int left, int top, int right, int down);
	
	int id;
	int left;
	int top;
	int right;
	int down;
};
#endif