#define _USE_MATH_DEFINES

#include "movement.h"
#include "param.h"
#include "random.h"

#include <cmath>

Movement::Movement(float minSpeed, float maxSpeed)
	: _minSpeed(minSpeed)
	, _maxSpeed(maxSpeed)
{}

Movement::~Movement() {}

void
Movement::init() {
	for (auto& agent : _simulation->getAgents()) {
		agent.x = Rand(_simulation->getWidth());
		agent.y = Rand(_simulation->getHeight());

		// Direction
		float angle = Rand((float)-M_PI, (float)M_PI);
		float speed = Rand(_minSpeed, _maxSpeed);
		agent.dx = speed * cos(angle);
		agent.dy = speed * sin(angle);
	}
}