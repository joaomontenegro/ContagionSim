#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "factory.h"
#include "agent.h"

class Collision
{
public:
	Collision(float radius);
	Collision(const Params& params);
	virtual ~Collision();

	float getRadius();

	bool collide(Agent& a, Agent& b);

private:
	float _radius;
	float _radius2;
};


namespace {
	RegisterEntity<Collision, Collision> _myCollision("MyCollision");
};


#endif // _COLLISION_H_
