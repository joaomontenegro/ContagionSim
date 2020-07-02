#ifndef _SIMPLE_DISEASE_H_
#define _SIMPLE_DISEASE_H_

#include "param.h"
#include "factory.h"
#include "disease.h"

class SimpleDisease : public Disease
{
public:
	SimpleDisease(const Params& params);
	~SimpleDisease();

	void transmit(Agent& agentA, Agent& agentB);

	void step(Agent& agent);
};

namespace {
	RegisterEntity<Disease, SimpleDisease> _myDisease("SimpleDisease");
};

#endif // _SIMPLE_DISEASE_H_