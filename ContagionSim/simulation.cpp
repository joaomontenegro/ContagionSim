#include "simulation.h"
#include "factory.h"
#include "log.h"
#include "collision.h"
#include "movement.h"
#include "disease.h"

Simulation::Simulation(const Params& params)
	: _width(params.get<float>("simulation.width", 500.0f))
	, _height(params.get<float>("simulation.height", 500.0f))
{

	// Agents need to be initialized before the plugins, since their
	// initialization might need the agents info ready.
	_isValid = _initAgents(params) && _initPlugins(params);
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

Agent&
Simulation::getAgent(size_t index)
{
	return _agents[index];
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

size_t
Simulation::getNumDead() const
{
	size_t num = 0;
	for (auto& agent : _agents) {
		if (agent.isDead()) {
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

	// Set the reference to this simulation in the plugins
	_collision->setSimulation(this);
	_movement->setSimulation(this);
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


	_agents.assign(numAgents, Agent());
	_collidedAgents.reserve(numAgents);

	return true;
}


