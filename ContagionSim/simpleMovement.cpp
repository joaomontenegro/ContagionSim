#include "simpleMovement.h"
#include "random.h"

SimpleMovement::SimpleMovement(const Params& params)
	: Movement(params.get<float>("movement.width", 400.0f),
		       params.get<float>("movement.height", 300.0f))
{}

SimpleMovement::~SimpleMovement() {}

void
SimpleMovement::move(AgentsVec& agents)
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
