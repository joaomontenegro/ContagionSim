#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include "plugin.h"
#include "agent.h"

class Movement : public Plugin
{
public:
	
	Movement(float minSpeed, float maxSpeed);
	virtual ~Movement();

	virtual void move() = 0;

protected:
	virtual void init();
	
	float _minSpeed;
	float _maxSpeed;
};


#endif // _MOVEMENT_H_