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

class MyCollision : public Collision
{
public:
	MyCollision(const Params& params)
		: Collision(ParamGet<float>(params, "radius", 3.5f))
	{}
	
	
	virtual ~MyCollision() = default;
};

namespace {
	RegisterEntity<Collision, MyCollision> _myCollision("MyCollision");
};


#endif // _COLLISION_H_
