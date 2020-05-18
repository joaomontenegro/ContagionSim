#ifndef _DISEASE_H_
#define _DISEASE_H_

#include "agent.h"

class Disease
{
public:
	Disease(float rate);
	~Disease();

	void transmit(Agent& agentA, Agent& agentB);

	void step(Agent& agent);
private:
	float _rate;
};

#endif // _DISEASE_H_