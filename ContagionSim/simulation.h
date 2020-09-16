#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include "param.h"
#include "agent.h"

// Forward declaration to avoid cyclical dependency
class Collision;
class Movement;
class Disease;

class Simulation
{
public:
	Simulation(const Params& params);
	~Simulation();

	bool isValid() { return _isValid; }
	void invalidate() { _isValid = false;  }
	
	void step();

	size_t getStepCount();

public:
	//** Getters **//
	float getWidth() const;
	float getHeight() const;

	const Collision* getCollision() const;
	const Movement*  getMovement() const;
	const Disease*   getDisease() const;

	AgentsVec& getAgents();
	Agent& getAgent(size_t index);
	size_t getNumAgents() const;
	size_t getNumSusceptible() const;
	size_t getNumAsymptomatic() const;
	size_t getNumSymptomatic() const;
	size_t getNumHospitalized() const;
	size_t getNumInfected() const;
	size_t getNumCured() const;
	size_t getNumDead() const;

private:
	bool _init();

	bool _initPlugins(const Params& params);
	bool _initAgents(const Params& params);
	
private:
	bool _isValid = false;
	
	size_t _stepCount = 0;

	float _width;
	float _height;
	
	Collision* _collision = nullptr;
	Movement*  _movement  = nullptr;
	Disease*   _disease   = nullptr;

	AgentsVec _agents;
	AgentsPairVec _collidedAgents;
};

#endif // _SIMULATION_H_