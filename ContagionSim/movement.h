#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include "factory.h"
#include "agent.h"
#include "param.h"

class Movement
{
public:
	
	Movement(float width, float height);
	Movement(const Params& params);
	virtual ~Movement();

	float getWidth();
	float getHeight();

	void move(AgentsVec& agents);

private:
	float _width;
	float _height;
};

namespace {
	RegisterEntity<Movement, Movement> _myMovement("MyMovement");
};

#endif // _MOVEMENT_H_