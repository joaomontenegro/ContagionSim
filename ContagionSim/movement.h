#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include "simulation.h"
#include "agent.h"

class Movement
{
public:
	
	Movement();
	virtual ~Movement();

	virtual void move() = 0;

	void setSimulation(Simulation* sim) { _simulation = sim; }

protected:
	Simulation* _simulation = nullptr;
};


#endif // _MOVEMENT_H_