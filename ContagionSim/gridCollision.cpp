#include "gridCollision.h"

GridCollision::GridCollision(const Params& params)
	: Collision(params.get<float>("collision.radius", 3.5f))
	, _gridSize(params.get<float>("collision.gridsize", 10.0f))
{}

GridCollision::~GridCollision() {}

bool
GridCollision::collide(Agent& a, Agent& b)
{
	return powf(a.x - b.x, 2) + powf(a.y - b.y, 2) < _radius2;
}
