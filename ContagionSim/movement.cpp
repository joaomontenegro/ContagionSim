#include "movement.h"
#include "random.h"

Movement::Movement(float width, float height)
	: _width(width),
	  _height(height)
{}

Movement::Movement(const Params& params)
	: Movement(params.get<float>("width", 400.0f),
		       params.get<float>("height", 300.0f))
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

void
Movement::move(AgentsVec& agents)
{
	for (Agent& agent : agents) {
		// Update position
		agent.x += agent.dx;
		agent.y += agent.dy;

		// Bounce off the arena walls
		if (agent.x < 0) { agent.dx *= -1; }
		if (agent.x >= _width) { agent.dx *= -1; }
		if (agent.y < 0) { agent.dy *= -1; }
		if (agent.y >= _height) { agent.dy *= -1; }

		// Update velocity
		agent.dx += Rand(-0.01f, 0.01f);
		agent.dy += Rand(-0.01f, 0.01f);
	}
}