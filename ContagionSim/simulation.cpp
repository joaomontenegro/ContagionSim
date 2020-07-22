#define _USE_MATH_DEFINES

#include "simulation.h"
#include "factory.h"
#include "random.h"
#include "log.h"
#include "collision.h"
#include "movement.h"
#include "disease.h"

Simulation::Simulation(const Params& params)
	: _width(params.get<float>("simulation.width", 500.0f))
	, _height(params.get<float>("simulation.height", 500.0f))
{
	_isValid = _initPlugins(params) && _initAgents(params);
}

Simulation::~Simulation() {}

void
Simulation::step()
{
	// Move all the agents and update their velocities
	_movement->move();

	// Detect any collision
	_collidedAgents.clear();
	_collision->collide(_collidedAgents);

	// Transmit the disease on the collisions and update
	// the disease in the agents.
	_disease->transmit(_collidedAgents);
    _disease->step();
}

float
Simulation::getWidth() const
{
	return _width;
}

float
Simulation::getHeight() const
{
	return _height;
}

const Collision*
Simulation::getCollision() const
{
	return _collision;
}

const Movement*
Simulation::getMovement() const
{
	return _movement;
}

const Disease*
Simulation::getDisease() const
{
	return _disease;
}

AgentsVec&
Simulation::getAgents()
{
	return _agents;
}

size_t
Simulation::getNumAgents() const
{
	return _agents.size();
}

size_t
Simulation::getNumSusceptible() const
{
	size_t num = 0;
	for (auto& agent : _agents) {
		if (agent.isSusceptible()) {
			num++;
		}
	}

	return num;
}

size_t
Simulation::getNumInfected() const
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
Simulation::getNumCured() const
{
	size_t num = 0;
	for (auto& agent : _agents) {
		if (agent.isCured()) {
			num++;
		}
	}

	return num;
}




bool
Simulation::_initPlugins(const Params& params)
{
	// Collision Plugin
	std::string colKey = params.get<std::string>("collision", "SimpleCollision");
	_collision = CreateEntity<Collision>(colKey, params);
	if (!_collision) {
		Log::error("Invalid Collision Plugin: " + colKey);
		return false;
	} else {
		Log::info("Collision Plugin: " + colKey);
	}
	_collision->setSimulation(this);
	
	// Movement Plugin
	std::string movKey = params.get<std::string>("movement", "SimpleMovement");
	_movement = CreateEntity<Movement>(movKey, params);
	if (!_movement) {
		Log::error("Invalid Movement Plugin: " + movKey);
		return false;
	} else {
		Log::info(" Movement Plugin: " + movKey);
	}
	_movement->setSimulation(this);

	// Disease Plugin
	std::string disKey = params.get<std::string>("disease", "SimpleDisease");
	_disease = CreateEntity<Disease>(disKey, params);
	if (!_disease) {
		Log::error("Invalid Disease Plugin: " + disKey);
		return false;
	} else {
		Log::info("  Disease Plugin: " + disKey);
	}
	_disease->setSimulation(this);

	return true;
}

bool
Simulation::_initAgents(const Params& params)
{
	int numAgents = params.get<int>("simulation.numAgents", 0);

	if (numAgents <= 0) {
		Log::error("Invalid number of agents: " + std::to_string(numAgents));
		return false;
	}

	for (int i = 0; i < numAgents; ++i) {
		Agent agent;
		agent.x = Rand(_width);
		agent.y = Rand(_height);

		// Direction
		float angle = Rand((float)-M_PI, (float)M_PI);
		float minSpeed = params.get<float>("agent.minSpeed", 0.1f);
		float maxSpeed = params.get<float>("agent.maxSpeed", 1.0f);
		float speed = Rand(minSpeed, maxSpeed);
		agent.dx = speed * cos(angle);
		agent.dy = speed * sin(angle);

		// Infected
		if (i < params.get<int>("simulation.numInitialInfected", 1)) {
			agent.state = Agent::State::Infected;
			agent.infectionAge = 0;
		}
		else {
			agent.state = Agent::State::Susceptible;
			agent.infectionAge = -1;
		}

		_agents.push_back(agent);
	}

	_collidedAgents.reserve(numAgents);

	return true;
}


