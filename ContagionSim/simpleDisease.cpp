#include "simpleDisease.h"
#include "random.h"

SimpleDisease::SimpleDisease(const Params& params)
	: Disease(params.get<float>("disease.rate", 0.1f))
{}

SimpleDisease::~SimpleDisease() {}

void
SimpleDisease::transmit(Agent& agentA, Agent& agentB)
{
	if (agentA.isInfected() != agentB.isInfected()) {
		if (SampleProbability(_rate)) {
			if (agentA.isHealthy()) { agentA.infectionAge = 0; }
			if (agentB.isHealthy()) { agentB.infectionAge = 0; }
		}
	}
}

void
SimpleDisease::step(Agent& agent)
{
	// Update infection
	if (agent.infectionAge >= 0) {
		// TODO: Take time step into account
		agent.infectionAge++;

		if (agent.infectionAge > 2000) {
			agent.infectionAge = -2;
		}
	}
}
