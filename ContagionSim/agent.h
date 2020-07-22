#ifndef _AGENT_H_
#define _AGENT_H_

#include <vector>

struct Agent {

	enum class State {Susceptible, Infected, Cured, Dead};

	float x = 0;
	float y = 0;

	float dx = 0;
	float dy = 0;

	State state = State::Susceptible;
	int infectionAge = -1;

	// TODO:
	bool isSusceptible() const { return state == State::Susceptible; }
	bool isInfected() const { return state == State::Infected; }
	bool isCured() const { return state == State::Cured; }
	bool isDead() const { return state == State::Dead; }

	void infect() { state = State::Infected; infectionAge = 0; }
	void cure() { state = State::Cured; }
	void kill() { state = State::Dead; }
};

typedef std::vector<Agent> AgentsVec;
typedef std::pair<Agent&, Agent&> AgentsPair;
typedef std::vector<AgentsPair> AgentsPairVec;


#endif // _AGENT_H_