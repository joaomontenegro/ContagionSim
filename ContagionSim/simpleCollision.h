#ifndef _SIMPLE_COLLISION_H_
#define _SIMPLE_COLLISION_H_

#include "factory.h"
#include "param.h"
#include "collision.h"

class SimpleCollision : public Collision
{
public:
	SimpleCollision(const Params& params);
	virtual ~SimpleCollision();

	virtual bool collide(Agent& a, Agent& b);
};

namespace {
	RegisterEntity<Collision, SimpleCollision> _simpleCollision("SimpleCollision");
};


#endif
