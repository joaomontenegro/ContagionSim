#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include "simulation.h"
#include "agent.h"

class Movement
{
public:
	
	Movement();
	virtual ~Movement();

	virtual void move(AgentsVec& agents) = 0;

	void setSimulation(const Simulation* sim) { _simulation = sim; }

protected:
	const Simulation* _simulation = nullptr;
};


#endif // _MOVEMENT_H_