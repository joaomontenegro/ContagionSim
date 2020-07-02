#ifndef _DISEASE_H_
#define _DISEASE_H_

#include "agent.h"

class Disease
{
public:
	Disease(float rate);
	~Disease();

	virtual void transmit(Agent& agentA, Agent& agentB) = 0;

	virtual void step(Agent& agent) = 0;

protected:
	float _rate;
};


#endif // _DISEASE_H_