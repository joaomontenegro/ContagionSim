#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include "agent.h"
#include "arena.h"

class Movement
{
public:
	
	Movement(Arena* arena);
	virtual ~Movement();

	void move(AgentsVec& agents);

private:
	Arena* _arena;
};

#endif // _MOVEMENT_H_