#define _USE_MATH_DEFINES

#include "simulation.h"
#include "factory.h"
#include "random.h"
#include "log.h"

Simulation::Simulation(const Params& params)
{
	_isValid = _initPlugins(params) && _initAgents(params);
}

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
	
	// Movement Plugin
	std::string movKey = params.get<std::string>("movement", "SimpleMovement");
	_movement = CreateEntity<Movement>(movKey, params);
	if (!_movement) {
		Log::error("Invalid Movement Plugin: " + movKey);
		return false;
	} else {
		Log::info(" Movement Plugin: " + movKey);
	}

	// Disease Plugin
	std::string disKey = params.get<std::string>("disease", "SimpleDisease");
	_disease = CreateEntity<Disease>(disKey, params);
	if (!_disease) {
		Log::error("Invalid Disease Plugin: " + disKey);
		return false;
	} else {
		Log::info("  Disease Plugin: " + disKey);
	}

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
		agent.x = Rand(_movement->getWidth());
		agent.y = Rand(_movement->getHeight());

		// Direction
		float angle = Rand((float)-M_PI, (float)M_PI);
		float minSpeed = params.get<float>("agent.minSpeed", 0.1f);
		float maxSpeed = params.get<float>("agent.maxSpeed", 1.0f);
		float speed = Rand(minSpeed, maxSpeed);
		agent.dx = speed * cos(angle);
		agent.dy = speed * sin(angle);

		// Infected
		if (i < params.get<int>("simulation.numInitialInfected", 1)) {
			agent.infectionAge = 0;
		}
		else {
			agent.infectionAge = -1;
		}

		_agents.push_back(agent);
	}

	return true;
}


