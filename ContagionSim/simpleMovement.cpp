#include "simpleMovement.h"
#include "random.h"

SimpleMovement::SimpleMovement(const Params& params) 
	: Movement(params.get<float>("movement.minSpeed", 0.1f),
		       params.get<float>("movement.maxSpeed", 1.0f))
{}

SimpleMovement::~SimpleMovement() {}

void
SimpleMovement::move()
{
	for (Agent& agent : _simulation->getAgents()) {

		if (agent.isDead()) {
			continue;
		}

		// Get the velocity
		float dx = agent.dx;
		float dy = agent.dy;

		// Update position
		agent.x += dx;
		agent.y += dy;

		// Bounce off the arena walls
		if (agent.x < 0) { agent.dx *= -1; }
		if (agent.x >= _simulation->getWidth()) { agent.dx *= -1; }
		if (agent.y < 0) { agent.dy *= -1; }
		if (agent.y >= _simulation->getHeight()) { agent.dy *= -1; }

		// TODO
		// Update velocity
		//agent.dx += Rand(-0.01f, 0.01f);
		//agent.dy += Rand(-0.01f, 0.01f);
	}
}
