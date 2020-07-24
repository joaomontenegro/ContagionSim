#include "simpleDisease.h"
#include "random.h"

SimpleDisease::SimpleDisease(const Params& params)
	: Disease(params.get<float>("disease.transmitionRate", 0.1f))
	, _cureTime(params.get<int>("disease.cureTime", 1000))
{}

SimpleDisease::~SimpleDisease() {}

void
SimpleDisease::transmit(AgentsPairVec& agentPairs)
{
	for (auto& ap : agentPairs) {
		Agent& agentA = ap.first;
		Agent& agentB = ap.second;

		if (agentA.isInfected() || agentB.isInfected()) {
			if (SampleProbability(_transmissionRate)) {
				if (agentA.isSusceptible()) { agentA.infect(); }
				if (agentB.isSusceptible()) { agentB.infect(); }
			}
		}
	}
}

void
SimpleDisease::step()
{
	for (auto& agent : _simulation->getAgents()) {
		// Update infection
		if (agent.infectionAge >= 0) {
			// TODO: Take time step into account
			agent.infectionAge++;

			if (agent.infectionAge > _cureTime) {
				agent.cure();
			}
		}
	}
}
