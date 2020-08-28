#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "simulation.h"

class GLRenderer
{
public:
	GLRenderer(Simulation* sim) : _sim(sim) {}
	virtual ~GLRenderer() {}

	virtual void render() = 0;

protected:
	Simulation* _sim;
};

#endif
