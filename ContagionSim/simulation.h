#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include "param.h"
#include "agent.h"
#include "collision.h"
#include "movement.h"
#include "disease.h"

class Simulation
{
public:
	Simulation(const Params& params);
	~Simulation();

	bool isValid() { return _isValid; }
	
	void step();

public:
	//** Getters **//
	const AgentsVec& getAgents() { return _agents; }

	float getCollisionRadius() { return _collision->getRadius(); }

	size_t getNumAgents() { return _agents.size(); }
	size_t getNumHealthy();
	size_t getNumInfected();
	size_t getNumCured();

	float getWidth();
	float getHeight();

private:
	bool _initPlugins(const Params& params);
	bool _initAgents(const Params& params);
	
private:
	bool _isValid = false;
	
	Collision* _collision = nullptr;
	Movement*  _movement  = nullptr;
	Disease*   _disease   = nullptr;

	AgentsVec _agents;
};

#endif // _SIMULATION_H_