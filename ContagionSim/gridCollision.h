#ifndef _GRID_COLLISION_H_
#define _GRID_COLLISION_H_

#include "factory.h"
#include "param.h"
#include "collision.h"

class GridCollision : public Collision
{
public:
	GridCollision(const Params& params);
	virtual ~GridCollision();

	virtual bool collide(Agent& a, Agent& b);

private:
	float _gridSize;
};

namespace {
	RegisterEntity<Collision, GridCollision> _GridCollision("GridCollision");
};

#endif
