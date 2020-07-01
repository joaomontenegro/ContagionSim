#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include "agent.h"
#include "collision.h"
#include "movement.h"
#include "disease.h"

class Simulation
{
public:
	Simulation(int numAgents,
			   Collision* collision,
			   Movement* movement,
		       Disease* disease);

	Simulation(const Params& params,
		       Collision* collision,
		       Movement* movement,
		       Disease* disease);

	~Simulation();

	void step();

	const AgentsVec& getAgents() { return _agents; }

	float getCollisionRadius() { return _collision->getRadius(); }

	size_t getNumAgents() { return _agents.size(); }
	size_t getNumHealthy();
	size_t getNumInfected();
	size_t getNumCured();

	float getWidth();
	float getHeight();

private:
	AgentsVec _agents;
	Collision* _collision;
	Movement* _movement;
	Disease* _disease;
};

#endif // _SIMULATION_H_