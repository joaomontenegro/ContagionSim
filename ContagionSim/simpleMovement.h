#ifndef _SIMPLE_MOVEMENT_H_
#define _SIMPLE_MOVEMENT_H_

#include "factory.h"
#include "param.h"
#include "movement.h"

class SimpleMovement : public Movement
{
public:

	SimpleMovement(const Params& params);
	virtual ~SimpleMovement();

	virtual void move(AgentsVec& agents);
};

namespace {
	RegisterEntity<Movement, SimpleMovement> _simpleMovement("SimpleMovement");
};


#endif

