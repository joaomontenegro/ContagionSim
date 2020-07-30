#ifndef _AGENT_H_
#define _AGENT_H_

#include <vector>

struct Agent {

	enum class State {
		Susceptible,
		Asymptomatic,
		Symptomatic,
		Hospitalized,
		Dead,
		Cured
	};

	float x = 0;
	float y = 0;

	float dx = 0;
	float dy = 0;

	State state = State::Susceptible;
	int infectionAge = 0;
	bool canSpread = true;

	// TODO:
	inline bool isSusceptible() const { return state == State::Susceptible; }
	inline bool isCured() const { return state == State::Cured; }
	inline bool isAsymptomatic() const { return state == State::Asymptomatic; }
	inline bool isSymptomatic() const { return state == State::Symptomatic; }
	inline bool isHospitalized() const { return state == State::Hospitalized; }
	inline bool isDead() const { return state == State::Dead; }

	inline bool isInfected() const
	{
		return isAsymptomatic() || isSymptomatic() || isHospitalized();
	}

	void infect() { state = State::Asymptomatic; infectionAge = 0; }
	void startSymptoms() { state = State::Symptomatic; }
	void hospitalize() { state = State::Hospitalized; }
	void kill() { state = State::Dead; }
	void cure() { state = State::Cured; }
};

typedef std::vector<Agent> AgentsVec;
typedef std::pair<Agent&, Agent&> AgentsPair;
typedef std::vector<AgentsPair> AgentsPairVec;


#endif // _AGENT_H_