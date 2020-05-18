#include "disease.h"
#include "random.h"

Disease::Disease(float rate)
	: _rate(rate)
{
	if (_rate > 1.0f) {
		_rate = 1.0f;
	}
}

Disease::~Disease() {}

void
Disease::transmit(Agent& agentA, Agent& agentB)
{
	if (agentA.isInfected() != agentB.isInfected()) {
		if (SampleProbability(_rate)) {
			if (agentA.isHealthy()) { agentA.infectionAge = 0; }
			if (agentB.isHealthy()) { agentB.infectionAge = 0; }
		}
	}
}

void
Disease::step(Agent& agent)
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