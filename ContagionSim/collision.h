#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "factory.h"
#include "agent.h"

// TODO: deal with all the collisions

class Collision
{
public:
	Collision(float radius);
	virtual ~Collision();

	bool collide(Agent& a, Agent& b);

	float getRadius();

private:
	float _radius;
	float _radius2;
};


#endif // _COLLISION_H_
