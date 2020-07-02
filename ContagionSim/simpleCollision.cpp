#include "simpleCollision.h"

SimpleCollision::SimpleCollision(const Params& params)
	: Collision(params.get<float>("collision.radius", 3.5f))
{}

SimpleCollision::~SimpleCollision() {}

bool
SimpleCollision::collide(Agent& a, Agent& b)
{
	return powf(a.x - b.x, 2) + powf(a.y - b.y, 2) < _radius2;
}