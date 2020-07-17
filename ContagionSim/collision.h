#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "simulation.h"
#include "agent.h"

class Collision
{
public:
	Collision(float radius);
	virtual ~Collision();

	virtual void collide(AgentsPairVec& result) = 0;

	void setSimulation(Simulation* sim) { _simulation = sim; }

	float getRadius() const;

protected:
	float _radius;
	float _radius2;

	Simulation* _simulation = nullptr;
};




#endif // _COLLISION_H_
