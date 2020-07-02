#include "movement.h"

Movement::Movement(float width, float height)
	: _width(width),
	  _height(height)
{}

Movement::~Movement() {}

float
Movement::getWidth()
{
	return _width;
}

float
Movement::getHeight()
{
	return _height;
}
