#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "simulation.h"

#include <SDL.h>

class GLRenderer
{
public:
	GLRenderer(Simulation* sim) : _sim(sim) {}
	virtual ~GLRenderer() {}

	virtual void render(SDL_Renderer* sdlRenderer=nullptr) = 0;

protected:
	Simulation* _sim;
};

#endif
