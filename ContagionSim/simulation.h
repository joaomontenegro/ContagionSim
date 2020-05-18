#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include "agent.h"
#include "arena.h"
#include "collision.h"
#include "movement.h"
#include "disease.h"

class Simulation
{
public:
	Simulation(int numAgents,
		       Arena* arena,
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

	float getWidth()  { return _arena->width;  }
	float getHeight() { return _arena->height; }

private:
	AgentsVec _agents;
	Arena* _arena;
	Collision* _collision;
	Movement* _movement;
	Disease* _disease;
};

#endif // _SIMULATION_H_