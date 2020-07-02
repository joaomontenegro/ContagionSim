#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include "agent.h"

class Movement
{
public:
	
	Movement(float width, float height);
	virtual ~Movement();

	float getWidth();
	float getHeight();

	virtual void move(AgentsVec& agents) = 0;

protected:
	float _width;
	float _height;
};


#endif // _MOVEMENT_H_