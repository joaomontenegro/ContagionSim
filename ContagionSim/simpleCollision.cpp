#include "simpleCollision.h"

SimpleCollision::SimpleCollision(const Params& params)
	: Collision(params.get<float>("collision.radius", 3.5f))
{}

SimpleCollision::~SimpleCollision() {}

void
SimpleCollision::collide(AgentsPairVec& result)
{
	AgentsVec& agents = _simulation->getAgents();

	// Collision with other agents
	for (size_t i = 0; i < agents.size(); ++i) {
		Agent& agent = agents[i];

		for (size_t j = i + 1; j < agents.size(); ++j) {
			Agent& other = agents[j];
			if (calcCollision(agent, other)) {
				result.push_back(AgentsPair(agent, other));
			}
		}
	}
}

bool
SimpleCollision::calcCollision(const Agent & a, const Agent & b)
{
	return powf(a.x - b.x, 2) + powf(a.y - b.y, 2) < _radius2;
}
