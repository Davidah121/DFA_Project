#include "Box.h"



Box::Box()
{
}

Box::Box(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Box::Box(const Box & c)
{
	x = c.x;
	y = c.y;
	width = c.width;
	height = c.height;
}


Box::~Box()
{
}
