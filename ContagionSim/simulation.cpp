#define _USE_MATH_DEFINES

#include "simulation.h"
#include "random.h"

Simulation::Simulation(int numAgents,
	                   Collision* collision,
					   Movement* movement,
	                   Disease* disease)
	: _agents(numAgents)
	, _collision(collision)
	, _movement(movement)
	, _disease(disease)
{
	for (size_t i = 0; i < _agents.size(); ++i) {
		Agent& agent = _agents[i];
		agent.x = Rand(_movement->getWidth());
		agent.y = Rand(_movement->getHeight());

		// Direction
		float angle = Rand((float)-M_PI, (float)M_PI);
		float speed = Rand(0.1f, 1.0f); // TODO parameterize
		agent.dx = speed * cos(angle);
		agent.dy = speed * sin(angle);

		// TODO: specify percentage infected & cured at beginning
		// Infected
		size_t NUM_INFECTED = 1;
		if (i < NUM_INFECTED) {
			agent.infectionAge = 0;
		} else {
			agent.infectionAge = -1;
		}
	}
}

Simulation::Simulation(const Params& params,
				       Collision* collision,
				       Movement* movement,
				       Disease* disease)
	: Simulation(params.get<int>("numAgents", 100),
		collision,
		movement,
		disease)
{}

Simulation::~Simulation() {}

void
Simulation::step()
{
	// Move all the agents and update their velocities
	_movement->move(_agents);

	// Collision with other agents
	for (size_t i = 0; i < _agents.size(); ++i) {
		Agent& agent = _agents[i];
		
		for (size_t j = i + 1; j < _agents.size(); ++j) {
			Agent& other = _agents[j];
			if (_collision->collide(agent, other)) {
				_disease->transmit(agent, other);
			}
		}

		// Update disease
		_disease->step(agent);		
	}
}

size_t
Simulation::getNumHealthy()
{
	size_t num = 0;
	for (auto& agent : _agents) {
		if (agent.isHealthy()) {
			num++;
		}
	}

	return num;
}

size_t
Simulation::getNumInfected()
{
	size_t num = 0;
	for (auto& agent : _agents) {
		if (agent.isInfected()) {
			num++;
		}
	}

	return num;
}

size_t
Simulation::getNumCured()
{
	size_t num = 0;
	for (auto& agent : _agents) {
		if (agent.isCured()) {
			num++;
		}
	}

	return num;
}

float
Simulation::getWidth()
{
	return _movement->getWidth();
}

float
Simulation::getHeight()
{
	return _movement->getHeight();
}
