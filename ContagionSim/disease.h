#ifndef _DISEASE_H_
#define _DISEASE_H_

#include "simulation.h"
#include "agent.h"

class Disease
{
public:
	Disease(float rate);
	~Disease();

	virtual void transmit(AgentsPairVec& agentPairs) = 0;

	virtual void step() = 0;

	void setSimulation(Simulation* sim) { _simulation = sim; init(); }

protected:
	virtual void init() = 0;

	float _transmissionRate;

	Simulation* _simulation = nullptr;
};


#endif // _DISEASE_H_