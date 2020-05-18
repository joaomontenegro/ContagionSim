#ifndef _AGENT_H_
#define _AGENT_H_

#include <vector>

struct Agent {
	float x = 0;
	float y = 0;

	float dx = 0;
	float dy = 0;

	int infectionAge = -1;

	bool isInfected() const { return infectionAge >= 0; }
	bool isCured() const { return infectionAge == -2; }
	bool isHealthy() const { return infectionAge == -1; }
};

typedef std::vector<Agent> AgentsVec;

#endif // _AGENT_H_