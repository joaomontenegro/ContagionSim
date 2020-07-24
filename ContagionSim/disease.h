#ifndef _DISEASE_H_
#define _DISEASE_H_

#include "plugin.h"
#include "agent.h"

class Disease : public Plugin
{
public:
	Disease(float transmissionRate, int numInitialInfected);
	~Disease();

	virtual void transmit(AgentsPairVec& agentPairs) = 0;

	virtual void step() = 0;

protected:
	virtual void init();

	float _transmissionRate;
	size_t _numInitialInfected;
};


#endif // _DISEASE_H_