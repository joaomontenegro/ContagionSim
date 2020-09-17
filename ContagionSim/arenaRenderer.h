#ifndef _ARENA_RENDERER_H_
#define _ARENA_RENDERER_H_

#include "renderer.h"

class ArenaRenderer : public GLRenderer
{
public:
	ArenaRenderer(Simulation* sim);
	virtual ~ArenaRenderer();

public:
	void render(SDL_Renderer* _sdlRenderer) override;

private:
	bool _renderInfected = false; //todo
	SDL_Point* _positions;
};

#endif
