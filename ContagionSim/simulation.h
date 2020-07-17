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
	
	void step();

public:
	//** Getters **//
	float getWidth() const;
	float getHeight() const;

	const Collision* getCollision() const;
	const Movement*  getMovement() const;
	const Disease*   getDisease() const;

	AgentsVec& getAgents();
	size_t getNumAgents() const;
	size_t getNumHealthy() const;
	size_t getNumInfected() const;
	size_t getNumCured() const;

private:
	bool _initPlugins(const Params& params);
	bool _initAgents(const Params& params);
	
private:
	bool _isValid = false;

	float _width;
	float _height;
	
	Collision* _collision = nullptr;
	Movement*  _movement  = nullptr;
	Disease*   _disease   = nullptr;

	AgentsVec _agents;
	AgentsPairVec _collidedAgents;
};

#endif // _SIMULATION_H_