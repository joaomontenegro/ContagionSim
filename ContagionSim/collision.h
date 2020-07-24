#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "plugin.h"
#include "agent.h"

class Collision : public Plugin
{
public:
	Collision(float radius);
	virtual ~Collision();

	virtual void collide(AgentsPairVec& result) = 0;

	float getRadius() const;

protected:
	virtual void init() {}

	float _radius;
	float _radius2;
};




#endif // _COLLISION_H_
