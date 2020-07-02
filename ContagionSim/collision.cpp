#include "collision.h"

Collision::Collision(float radius)
	: _radius(radius)
	, _radius2(_radius * _radius)
{}

Collision::~Collision() {}

float
Collision::getRadius()
{
	return _radius;
}
