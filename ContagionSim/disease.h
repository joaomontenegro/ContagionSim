#ifndef _DISEASE_H_
#define _DISEASE_H_

#include "factory.h"
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

class MyDisease : public Disease
{
public:
	MyDisease() : Disease(0.1f) {}
	virtual ~MyDisease() = default;
};

/*
namespace {
	RegisterEntity<Disease, MyDisease> _myDisease("MyDisease");
};
*/

#endif // _DISEASE_H_