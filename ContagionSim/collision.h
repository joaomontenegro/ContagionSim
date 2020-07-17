#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "agent.h"

class Collision
{
public:
	Collision(float radius);
	virtual ~Collision();

	float getRadius() const;

	virtual bool collide(Agent& a, Agent& b) = 0;

protected:
	float _radius;
	float _radius2;
};




#endif // _COLLISION_H_
