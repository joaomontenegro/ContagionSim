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

bool
Collision::collide(Agent& a, Agent& b)
{
	return powf(a.x - b.x, 2) + powf(a.y - b.y, 2) < _radius2;
}