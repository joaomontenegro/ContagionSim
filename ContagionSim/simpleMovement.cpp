#define _USE_MATH_DEFINES

#include "simpleMovement.h"
#include "random.h"

SimpleMovement::SimpleMovement(const Params& params) 
	: Movement(params.get<float>("movement.minSpeed", 0.1f),
		       params.get<float>("movement.maxSpeed", 1.0f))
	, _dirChangeAngle(params.get<float>("movement.dirChangeAngle", 0.0f) * float(M_PI) / 180.0f )
{}

SimpleMovement::~SimpleMovement() {}

#include <iostream>

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

		// Update velocity
		float a = Rand(-_dirChangeAngle, _dirChangeAngle);
		float cosA = cos(a);
		float sinA = sin(a);
		agent.dx = dx * cosA - dy * sinA;
		agent.dy = dx * sinA + dy * cosA;

		// Update position
		agent.x += dx;
		agent.y += dy;

		// Bounce off the arena walls
		if (agent.x < 0) { agent.dx *= -1; agent.x = 0.0f; }
		if (agent.x >= _simulation->getWidth()) { agent.dx *= -1;  agent.x = _simulation->getWidth() - 1;  }
		if (agent.y < 0) { agent.dy *= -1; agent.y = 0.0f; }
		if (agent.y >= _simulation->getHeight()) { agent.dy *= -1; agent.y = _simulation->getHeight() - 1;  }
	}
}
