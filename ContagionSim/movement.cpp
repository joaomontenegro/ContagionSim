#include "movement.h"
#include "random.h"

Movement::Movement(Arena* arena)
	: _arena(arena)
{}

Movement::~Movement() {}

void
Movement::move(AgentsVec& agents)
{
	for (Agent& agent : agents) {
		// Update position
		agent.x += agent.dx;
		agent.y += agent.dy;

		// Bounce off the arena walls
		if (agent.x < 0) { agent.dx *= -1; }
		if (agent.x >= _arena->width) { agent.dx *= -1; }
		if (agent.y < 0) { agent.dy *= -1; }
		if (agent.y >= _arena->height) { agent.dy *= -1; }

		// Update velocity
		agent.dx += Rand(-0.01f, 0.01f);
		agent.dy += Rand(-0.01f, 0.01f);
	}
}